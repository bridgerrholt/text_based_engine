/// @file engine.cpp
/// Definition of the class tbe::Engine.

#include "engine.h"

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <locale>

#include <dep/check_file_exists.h>
#include <dep/is_int.h>
#include <dep/of_dynamic.h>
#include <dep/sleep_event.h>
#include <dep/print_line.h>
#include <dep/to_underlying_value.h>

#include "dev_tools/types/types.h"

#include "ask_question.h"
#include "dev_tools/run_info.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <sqlite3.h>

namespace tbe {

class EngineData
{
	public:
		/// The locale used.
		std::locale locale;

		/// Primary InputManager.
		dep::InputManager inputManager;
		
		/// Path to the root of the application.
		std::string rootPath;

		dev_tools::CommandProcessor commandProcessor;
};


}


namespace {

using namespace tbe;
using namespace tbe::dev_tools;

namespace states
{
	constexpr char
		BAD[]             = "bad",
		LOBBY[]           = "lobby",
		PLAYER_RESPONSE[] = "player_response";

};



class Execution
{
	public:
		/// Highest-level constructor.
		/// Meant to take in the supplied terminal commands. Opens the database if provided,
		/// otherwise asks for one.
		Execution(EngineData & engineData, int argc, char* argv[]);

		Execution(EngineData & engineData, std::string const & fileName);

		/// Unloads the database (if opened) and all active queries.
		~Execution();


	private:
		class OptionDisplay
		{
			public:
				ResponseOptionList options;
				std::string        startText;
				std::string        endText;
		};

		class FullOptionList
		{
			public:
				ResponseOptionList optionList;
				std::size_t        startNum;
				std::size_t        lastingOptionCount;

				void resize() { optionList.resize(lastingOptionCount); }
		};

		Execution(EngineData & engineData);

		void run();

		/// Opens the provided database and gathers needed data.
		/// If a database is already open, it is closed before the new one is opened.
		/// @param[in] fileName The path and name of the database file.
		void openDatabase(std::string const & fileName);

		bool databaseSetup(int argc, char* argv[]);

		/// Creates and opens a database, initializes the correct values.
		void createDatabase(std::string const & fileName);

		/// @param[out] command The command entered.
		/// @param[out] input   The player's input.
		/// @return Whether there was a command attempt.
		bool getInputCommand(dev_tools::RunInfo & command,
			std::string    & input);

		void processGenericCommand(dev_tools::RunInfo const & command);

		/// @return Whether they specified yes or no. Yes is true, no is false.
		bool promptBinaryOption(std::string const & question);

		bool createActor();

		FullOptionList& currentOptions();

		/// Decides whether the program should return to the lobby based on a passed value
		/// representing the next dialogue id.
		/// If it should return to the lobby, it also marks @ref state_ as @ref LOBBY.
		///
		/// @param[in] nextId If 0, the program should return to the lobby.
		/// @return Whether the program should return to the lobby or not.
		bool toLobby(int nextId);

		std::string fromRoot(std::string path) const;

		bool & getToQuit() {
			return stateMap_.getVariableValue<types::Bool>("to-quit");
		}

		bool & getDevMode() {
			return stateMap_.getVariableValue<types::Bool>("dev-mode");
		}

		EngineData & engineData_;


		std::unique_ptr<SQLite::Database> database_;

		/// All the actors specified in the database.
		std::unique_ptr<SQLite::Statement> actors_;

		/// Primary SleepEvent.
		/// Secondary SleepEvents may be added in the future.
		dep::SleepEvent sleepEvent_ = 500;

		dev_tools::StateMap & stateMap_;
		//dev_tools::StateMap::StateContainer::key_type const & currentState_;

		std::unordered_map<dev_tools::StateMap::StateContainer::key_type,
			FullOptionList> stateOptions_;
};



Execution::Execution(EngineData & engineData) :
	engineData_(engineData),
	stateMap_(engineData_.commandProcessor.getStateMap())
{
	using namespace dev_tools::commands;

	dep::printLineErr("Execution constructor called");

	stateOptions_[states::BAD];
	stateOptions_[states::LOBBY] = { {"QUIT"}, 0, 1 };
	stateOptions_[states::PLAYER_RESPONSE] = { {}, 1, 0 };
	
	engineData_.commandProcessor.resetStateMap({}, {});
	auto & stateMap = engineData_.commandProcessor.getStateMap();
	stateMap.pushState(states::BAD, {});
	stateMap.pushState(states::LOBBY, {});
	stateMap.pushState(states::PLAYER_RESPONSE, {});
}


Execution::Execution(EngineData & engineData, int argc, char* argv[]) :
	Execution(engineData)
{
	if (!getToQuit() && databaseSetup(argc, argv))
		run();
}


Execution::Execution(EngineData & engineData, std::string const & fileName) :
	Execution(engineData)
{
	if (!getToQuit()) {
		openDatabase(fileName);
		run();
	}
}


Execution::~Execution()
{
	// Any member queries should be closed before the database is closed.

	dep::printLineErr("Execution destructor called");
}



void
Execution::run()
{
	using namespace dev_tools::commands;

	if (getToQuit()) return;

	// The contents of columns is swapped out with a fresh ColumnList.
	if (actors_) actors_->reset();

	// SQL statements.
	SQLite::Statement optionQuerySingle { *database_,
		"SELECT * FROM options WHERE id = ?" };

	SQLite::Statement optionQueryList { *database_,
		"SELECT * FROM options WHERE option_list_id = ?" };

	SQLite::Statement responseQuery { *database_,
		"SELECT * FROM responses WHERE id = ?" };

	SQLite::Statement currentActor { *database_,
		"SELECT * FROM actors WHERE id = ?" };


	// Start with an actor index of 0, indicating we're in the lobby and
	// haven't selected an actor to talk to.
	currentActor.bind(1, 0);
	stateMap_.setCurrentState(states::LOBBY);

	std::vector<int> optionIds;

	// The ID of the next actor response.
	int next { 0 };

	// Specifies how many options always remain while in the lobby.
	// primaryOptions is resized to it in the lobby in case actors change.
	const long constantOptionsCount { 1 };

	while (stateMap_.getCurrentState() != states::BAD) {
		bool toExit { false };

		// Printed after printing the options.
		std::string postText {};

		// First processing.
		if (stateMap_.getCurrentState() == states::LOBBY) {
			// Exit the function if the database doesn't contain any actors.
			if (actors_->getColumnCount() == 0) {
				dep::printLine("Nobody seems to be around.");

				if (createActor()) {
					actors_->reset();
					continue;
				}

				toExit = true;
				break;
			}
			else {
				// All the old actors are removed and all the current actors are added.
				stateOptions_[states::LOBBY].resize();
				actors_->reset();
				while (actors_->executeStep()) {
					stateOptions_[states::LOBBY].optionList.push_back(
						actors_->getColumn("name"));
				}

				postText = "Who would you like to talk to?";
			}
		}
		
		else if (stateMap_.getCurrentState() == states::PLAYER_RESPONSE) {
			// The conversation is ongoing until one of the actions points to the ID of 0.
			if (toLobby(next)) continue;

			responseQuery.reset();
			responseQuery.bind(1, next);

			bool valid = responseQuery.executeStep();
			assert(valid);

			// Outputs the actor's dialogue and sleeps.
			// %name%: %textSpeak%-sleep-
			std::cout << '\n' <<
				currentActor.getColumn("name") << ": " <<
				responseQuery.getColumn("text_speak") << sleepEvent_ << '\n';

			int nextOptionListId { responseQuery.getColumn("next_id") };

			// The conversation is over if the next ID is marked as 0.
			if (toLobby(nextOptionListId)) continue;


			optionQueryList.reset();
			optionQueryList.bind(1, nextOptionListId);

			if (!optionQueryList.executeStep()) {
				throw std::runtime_error(
					"No option list (within table \"options"
					"\") with the id of " + std::to_string(nextOptionListId)
				);
			}

			// Lists all the textDisplay strings from the options.
			currentOptions().optionList.clear();
			optionIds.clear();

			do {
				currentOptions().optionList.push_back(optionQueryList.getColumn("text_display"));
				optionIds.push_back(optionQueryList.getColumn("id"));
			} while (optionQueryList.executeStep());
		}

		else {
				toExit = true;
		}

		if (toExit) break;

		// Lists all the options for the current state.
		printResponseOptions(currentOptions().optionList,
			currentOptions().startNum);

		dep::printLine(postText);

		std::string inputString;

		bool isCommand { false };
		dev_tools::RunInfo command;

		// TODO: Make not error-prone due to unsigned mismatch.
		long optionIndex { 0 };
		std::size_t optionIndexCollect { 0 };

		// Gets the player input.
		while (true) {
			isCommand = false;
			if (getInputCommand(command, inputString)) {
				isCommand = (command.commandId != CommandId::NONE);
				// Player inputted a command.
				if (isCommand) {
					switch (command.commandId) {
						case CommandId::LIST_PATHS:
							// TODO: Handle all the different states, outputting the next dialogue for each option.
							break;

						default:
							/*throw std::runtime_error(
								"Unhandled command (" + std::to_string(
									dep::toUnderlyingValue(command.commandId)) + ")"
							);*/
							/*std::cout << "Unhandled command (" << 
									dep::toUnderlyingValue(command.commandId) << ")";*/
							break;
					}
				}
			}
			
			// Player inputted one of the listed options.
			else {
				if (processResponseIndex(inputString, currentOptions().optionList.size(),
					optionIndexCollect, currentOptions().startNum)) {
					optionIndex = (long)optionIndexCollect;

					if (stateMap_.getCurrentState() == states::LOBBY) {
						// All the constant options are handled.
						// QUIT
						if (optionIndex == 0) {
							toExit = true;
							break;
						}

						// The actor index must be offset backwards from the constant option offset.
						// In other words, to map the optionIndex to the actors_ list, the amount of
						// non-actor options must be subtracted.
						long id { optionIndex - constantOptionsCount + 1 };
						currentActor.reset();
						currentActor.bind(1, (long long)id);
						bool valid = currentActor.executeStep();
						assert(valid);

						// The ID of the next actor response.
						next = currentActor.getColumn("intro_id");

						// If the intro ID is 0, that indicates no conversation will take place.
						if (next == 0) {
							std::cout << currentActor.getColumn("name") <<
								" doesn't want to speak right now.\n";

							// Stays in the lobby.
							//break;
						}
						else {
							stateMap_.setCurrentState(states::PLAYER_RESPONSE);
						}

						//break;
					}

					else if (stateMap_.getCurrentState() == states::PLAYER_RESPONSE) {
						// Displays the user's response and sleeps.
						optionQuerySingle.reset();
						optionQuerySingle.bind(1, optionIds[optionIndex]);
						optionQuerySingle.executeStep();
						assert(!optionQuerySingle.isDone());

						std::cout << '\n' <<
							optionQuerySingle.getColumn("text_speak") << '\n' <<
							sleepEvent_;

						next = optionQuerySingle.getColumn("next_id");
					}

					else if (stateMap_.getCurrentState() == states::BAD) {
						toExit = true;
					}

					break;
				}
			}
		}

		if (toExit) break;
	}
}




void
Execution::openDatabase(std::string const & fileName)
{
	database_.reset(new SQLite::Database(
		fileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE
	));

	actors_.reset(new SQLite::Statement(*database_, "SELECT * FROM actors"));

	while (actors_->executeStep()) {
		std::cout << actors_->getColumn(0) << '\n';
	}
}



bool
Execution::databaseSetup(int argc, char* argv[])
{
	using namespace dev_tools::commands;

	std::cerr << "databaseSetup()\n";

	std::string fileName = engineData_.rootPath;

	if (argc >= 2)
		fileName += argv[1];

	// If there is no database file specified.
	else {
		std::cout << '\n';
		std::cout << "Must have a database.\n";

		while (true) {
			std::cout << "\nDatabase file name:\n";

			std::string inputString;
			dev_tools::RunInfo     command;

			// Keep prompting until the user enters something other than a command.
			while (getInputCommand(command, inputString)) {
				if (command.commandId == CommandId::QUIT) return false;
			}
			fileName += inputString;

			if (!dep::checkFileExists(fileName)) {
				if (promptBinaryOption(
					"That file cannot be found, create a new database?"
				)) {
					getDevMode() = true;
					createDatabase(fileName);
					return true;
				}

				else
					continue;
			}

			break;
		}
	}

	database_.reset(new SQLite::Database(
		fileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE
	));

	actors_.reset(new SQLite::Statement(*database_, "SELECT * FROM actors"));

	return true;
}



void
Execution::createDatabase(std::string const & fileName)
{
	database_.reset(new SQLite::Database(fileName));

	std::ifstream file { fromRoot("table_signatures.txt") };

	std::string frontText { "CREATE TABLE IF NOT EXISTS " };

	char        c;
	std::string toPush { frontText };
	bool        hasContents { false };

	SQLite::Statement stmt { *database_, "CREATE TABLE IF NOT EXISTS ?" };
	std::string tableName;

	while (file >> std::noskipws >> c) {
		if (!hasContents && std::isspace(c, engineData_.locale))
			continue;

		if (c == ';') {
			//std::cerr << "toPush: " << toPush << '\n';
			std::cerr << "tableName: " << tableName << '\n';

			stmt.bind(1, tableName);

			//toPush.erase(toPush.begin() + frontText.size(), toPush.end());
			hasContents = false;

			tableName = "";
		}
		else {
			tableName += c;
			hasContents = true;
		}
	}
}



bool
Execution::getInputCommand(dev_tools::RunInfo & command,
	std::string  & input)
{
	input = engineData_.inputManager.promptClean();

	if (input.empty())
		return true;

	command = engineData_.commandProcessor.readCommand(input);

	switch (command.state) {
		case dev_tools::RunInfo::NONE:
			return false;

		case dev_tools::RunInfo::VALID:
			processGenericCommand(command);

			return true;

		case dev_tools::RunInfo::INVALID:
			std::cout << "No such command\n";
			return true;

		default:
			throw std::runtime_error("Invalid CommandProcessor::InputInfo");
	}
}


void
Execution::processGenericCommand(dev_tools::RunInfo const & command)
{
	using namespace dev_tools::commands;

	switch (command.commandId) {
		case CommandId::NONE:
			// Fall-through
		default:
			break;
	}
}



bool
Execution::promptBinaryOption(std::string const & question)
{
	std::cout << question << std::endl;

	static
		ResponseOptionList binaryOptions { "Yes", "No" };

	printResponseOptions(binaryOptions);
	std::size_t input =
		getResponseIndex(engineData_.inputManager, binaryOptions.size());

	return (input == 0);
}



bool
Execution::createActor()
{
	if (!getDevMode()) return false;

	if (promptBinaryOption("Create an actor?")) {
		std::cout << "Actor name:\n";
		std::string actorName = engineData_.inputManager.promptClean();
		int introId = 0;

		SQLite::Statement countQuery { *database_, "SELECT COUNT(*) FROM actors" };
		countQuery.executeStep();
		introId = countQuery.getColumn(0);

		std::cerr << "actorName: " << actorName << '\n';
		std::cerr << "introId:   " << introId << '\n';

		std::string text {
			"INSERT INTO actors (name, intro_id) VALUES ('" +
				actorName + "', " +
				std::to_string(introId) + ");"
		};

		SQLite::Statement creation { *database_, text };
		creation.exec();

		return true;
	}

	else return false;
}



Execution::FullOptionList&
Execution::currentOptions()
{
	return stateOptions_.at(stateMap_.getCurrentState());
}



bool
Execution::toLobby(int nextId)
{
	if (nextId == 0) {
		stateMap_.setCurrentState(states::LOBBY);
		return true;
	}

	else return false;
}



std::string
Execution::fromRoot(std::string path) const
{
	return engineData_.rootPath + path;
}



}



namespace tbe {

Engine::Engine() :
	Engine(std::locale())
{

}


Engine::Engine(std::locale locale) :
	data_ (new EngineData {locale, {"> ", locale}, loadRoot(), {}})
{

}


Engine::Engine(int argc, char* argv[]) :
	Engine()
{
	run(argc, argv);
}



Engine::~Engine()
{
	// Any member queries should be closed before the database is closed.

	dep::printLineErr("Engine destructor called");
}



void
Engine::run(int argc, char* argv[])
{
	Execution e { *data_.get(), argc, argv };
}


void
Engine::run(std::string const & fileName)
{
	Execution e { *data_.get(), fileName };
}



void
Engine::setLocale(std::locale locale)
{
	data_->locale = std::move(locale);
}



std::string
Engine::loadRoot() const
{
	std::string rootFileName = "root.txt";
	assert(dep::checkFileExists(rootFileName));

	std::string toReturn;
	getline(std::ifstream { rootFileName }, toReturn);
	return toReturn;
}


}
