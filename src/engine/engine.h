/// @file engine.h
/// Declaration of the class tbe::Engine.

#ifndef TEXT_BASED_ENGINE_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_ENGINE_H

#include <locale>
#include <string>
#include <unordered_map>

#include <dep/input_manager.h>
#include <dep/sleep_event.h>
#include <dep/enum_class_hash.h>

//#include "../sql_support/common/query_result.h"

//#include "../sql_support/column_list.h"
//#include "../sql_support/database_handle.h"

#include "dev_tools/commands/kind.h"
#include "dev_tools/command_processor.h"
//#include "dev_tools/game_state_map.h"

#include <SQLiteCpp/SQLiteCpp.h>

#include "ask_question.h"

namespace tbe {


class RunInfo;

/// Provides the program's primary functionality.
/// An Engine object is used to load a given database and run the database's described game.
class Engine
{
	public:
		/// Default constructor.
		/// Doesn't actually load anything.
		Engine();

		/// Allows for a non-default locale.
		/// Called by all other constructors.
		/// @param[in] locale The explicitally-specified locale.
		Engine(std::locale locale);

		/// Highest-level constructor.
		/// Meant to take in the supplied terminal commands. Opens the database if provided,
		/// otherwise asks for one. Then calls run().
		Engine(int argc, char* argv[]);

		/// Unloads the database (if opened) and all active queries.
		~Engine();


		/// Opens the provided database and gathers needed data.
		/// If a database is already open, it is closed before the new one is opened.
		/// @param[in] fileName The path and name of the database file.
		void openDatabase(std::string const & fileName);


		/// Ensures there is a database then calls run().
		void run(int argc, char* argv[]);

		/// Calls loadDatabase() then run().
		/// @param[in] fileName The database file to be passed to loadDatabase().
		void run(std::string const & fileName);

		/// Runs the actual game.
		void run();


		/// @return Whether the user want to continue or not.
		bool databaseSetup(int argc, char* argv[]);


		/// Changes the locale.
		void setLocale(std::locale locale) { locale_ = std::move(locale); }


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
		};

		enum RunningState
		{
			/// Something is not right.
			BAD = 0,

			/// Lists all the characters.
			LOBBY,

			PLAYER_RESPONSE
		};

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

		void loadRoot();
		std::string fromRoot(std::string path) const;


		/// Whether the program should quit or not.
		bool toQuit = false;

		/// The program-wide locale.
		std::locale locale_;

		/// Primary InputManager.
		dep::InputManager inputManager_;

		std::unique_ptr<SQLite::Database> database_;

		/// All the actors specified in the database.
		std::unique_ptr<SQLite::Statement> actors_;

		/// Primary SleepEvent.
		/// Secondary SleepEvents may be added in the future.
		dep::SleepEvent sleepEvent_ = 500;

		/// Primary CommandProcessor.
		dev_tools::CommandProcessor commandProcessor_;

		RunningState state_ = BAD;

		bool inDevMode_ = false;

		std::unordered_map<RunningState,
			FullOptionList,
			dep::EnumClassHash> stateOptions_;

		/// Path to the root of the application.
		std::string rootPath_;
};


}

#endif