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

#include "dev_tools/types/common/include.h"

#include "ask_question.h"
#include "dev_tools/run_info.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <sqlite3.h>



namespace tbe {

Engine::Engine() :
  Engine(std::locale())
{

}


Engine::Engine(std::locale locale) :
  locale_(std::move(locale)),
  inputManager_("> ", locale_),
  commandProcessor_(dev_tools::StateMap::VariableMap(), dev_tools::StateMap::VariableMap())
{
  using namespace dev_tools::commands;

  dep::printLineErr("Engine constructor called");

  loadRoot();

  stateOptions_[BAD];
  stateOptions_[LOBBY] = {{}, 0};
  stateOptions_[PLAYER_RESPONSE] = {{}, 1};
  
  /*commandProcessor_.pushCommandState(BAD, { QUIT });
  commandProcessor_.pushCommandState(LOBBY, {});
  commandProcessor_.pushCommandState(PLAYER_RESPONSE, {});*/
  
  commandProcessor_.getStateMap().pushState("bad", {});
  commandProcessor_.getStateMap().pushState("lobby", {});
  commandProcessor_.getStateMap().pushState("player_response", {});

  /*stateMap_.insertGlobalVar<types::Bool>("dev",     false);
  stateMap_.insertGlobalVar<types::Bool>("to_quit", false);*/

  commandProcessor_.readCommandV2("hey there");

  /*

  enum class Command { SET };
  enum       State   { BAD, LOBBY };

  cp = CP();
  cp.pushState(BAD, { QUIT });

  */

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
Engine::openDatabase(std::string const & fileName)
{
  database_.reset(new SQLite::Database(
    fileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE
  ));

	actors_.reset(new SQLite::Statement(*database_, "SELECT * FROM actors"));

	while (actors_->executeStep()) {
		std::cout << actors_->getColumn(0) << '\n';
	}
}



void
Engine::run(int argc, char* argv[])
{
  if (toQuit) return;

  if (databaseSetup(argc, argv))
    run();
}


void
Engine::run(std::string const & fileName)
{
  if (toQuit) return;

  openDatabase(fileName);
  run();
}


void
Engine::run()
{
  using namespace dev_tools::commands;

  if (toQuit) return;
  
  // The contents of columns is swapped out with a fresh ColumnList.
  if (actors_) actors_->reset();
  
  SQLite::Statement optionQuerySingle { *database_, "SELECT * FROM options WHERE id = ?" };
	SQLite::Statement optionQueryList { *database_, "SELECT * FROM options WHERE option_list_id = ?" };

	SQLite::Statement responseQuery { *database_, "SELECT * FROM responses WHERE id = ?" };


  state_ = LOBBY;

  std::string nextResponse;

  //QueryObject * currentActor { 0 };
  SQLite::Statement currentActor { *database_, "SELECT * FROM actors WHERE id = ?" };
  currentActor.bind(1, 0);

  std::vector<int> optionIds;

  // The ID of the next actor response.
  int next { 0 };
  
  // Initialized before the main loop and resized in the lobby.
  ResponseOptionList primaryOptions;

  // Specifies how many options always remain while in the lobby.
  // primaryOptions is resized to it in the lobby in case actors change.
  const long constantOptionsCount { 1 };

  stateOptions_[LOBBY].optionList.push_back("QUIT"); // Breaks out of the main loop.

  while (state_ != BAD) {
    bool toExit { false };
    
    // Printed after printing the options.
    std::string postText { };

    // First processing.
    switch (state_) {
      case LOBBY :
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
          stateOptions_[LOBBY].optionList.resize(constantOptionsCount);
          actors_->reset();
          while (actors_->executeStep()) {
            stateOptions_[LOBBY].optionList.push_back(
              actors_->getColumn("name"));
          }

          postText = "Who would you like to talk to?";
        }

        break;

      case PLAYER_RESPONSE :
      {
        // The conversation is ongoing until one of the actions points to the ID of 0.
        if (toLobby(next)) continue;

        nextResponse = std::to_string(next);
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

        std::cerr << "Response: " << nextOptionListId << '\n';

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

        std::cerr << "Option text list\n";

        break;
      }

      case BAD : // Fallthrough
      default :
        toExit = true;
        break;
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
      if (getInputCommand(command, inputString)) {
        isCommand = (command.kind != NO_COMMAND);
      }

      else {
        if (processResponseIndex(inputString, currentOptions().optionList.size(),
                                 optionIndexCollect, currentOptions().startNum))
        {
	        optionIndex = (long)optionIndexCollect;
          std::cerr << "Processed " << optionIndex << '\n';
          break;
        }
      }

    }

    // Player inputted a command.
    if (isCommand) {
      switch (command.kind) {
        case QUIT :
          toExit = true;
          break;

        case LIST_PATHS :
          // TODO: Handle all the different states, outputting the next dialogue for each option.
          break;

        default :
          throw std::runtime_error(
            "Unhandled command (" + std::to_string(command.kind) + ")"
          );
      }
    }

    // Player inputted one of the listed options.
    else {
      switch (state_) {
        case LOBBY :
        {
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
          std::cerr << next << '\n';

          // If the intro ID is 0, that indicates no conversation will take place.
          if (next == 0) {
            std::cout << currentActor.getColumn("name") <<
              " doesn't want to speak right now.\n";

            // Stays in the lobby.
            break;
          }
          else {
            state_ = PLAYER_RESPONSE;
            std::cerr << "Wants to speak\n";
          }

          break;
        }
        case PLAYER_RESPONSE :
          std::cerr << "PLAYER_RESPONSE\n";
          // Displays the user's response and sleeps.
          optionQuerySingle.reset();
          optionQuerySingle.bind(1, optionIds[optionIndex]);
          optionQuerySingle.executeStep();
          assert(!optionQuerySingle.isDone());

          std::cout << '\n' <<
            optionQuerySingle.getColumn("text_speak") << '\n' <<
            sleepEvent_;

          next = optionQuerySingle.getColumn("next_id");
          std::cerr << "last next: " << next << '\n';
          break;

        case BAD :
          toExit = true;
          break;

        default:
          break;
      }
    }

    if (toExit) break;
  }
}



bool
Engine::databaseSetup(int argc, char* argv[])
{
  using namespace dev_tools::commands;

  std::cerr << "databaseSetup()\n";

  std::string fileName = rootPath_;

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
        if (command.kind == QUIT) return false;
      }
      fileName += inputString;
    
      if (!dep::checkFileExists(fileName)) {
        if (promptBinaryOption(
          "That file cannot be found, create a new database?"
        )) {
          inDevMode_ = true;
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
Engine::createDatabase(std::string const & fileName)
{
  database_.reset(new SQLite::Database(fileName));

  std::ifstream file { fromRoot("table_signatures.txt") };

  std::string frontText { "CREATE TABLE IF NOT EXISTS " };

  char        c;
  std::string toPush      { frontText };
  bool        hasContents { false };

  SQLite::Statement stmt { *database_, "CREATE TABLE IF NOT EXISTS ?" };
  std::string tableName;

  while (file >> std::noskipws >> c) {
    if (!hasContents && std::isspace(c, locale_))
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
Engine::getInputCommand(dev_tools::RunInfo & command,
                        std::string  & input)
{
  input = inputManager_.promptClean();
  std::cerr << "getInputCommand: " << input << '\n';

  if (input.empty())
    return true;

  command = commandProcessor_.readCommandV2(input);

  switch (command.state) {
    case dev_tools::RunInfo::NONE :
      return false;

    case dev_tools::RunInfo::VALID :
      processGenericCommand(command);
  
      return true;

    case dev_tools::RunInfo::INVALID :
      std::cout << "No such command\n";
      return true;

    default :
      throw std::runtime_error("Invalid CommandProcessor::InputInfo");
  }
}


void
Engine::processGenericCommand(dev_tools::RunInfo const & command)
{
  using namespace dev_tools::commands;

  switch (command.kind) {
    case DEV_ON :
      inDevMode_ = true;
      break;

    case QUIT :
      toQuit = true;
      break;

    case NO_COMMAND :
      // Fall-through
    default :
      break;
  }
}



bool
Engine::promptBinaryOption(std::string const & question)
{
  std::cout << question << std::endl;

  static
  ResponseOptionList binaryOptions { "Yes", "No" };

  printResponseOptions(binaryOptions);
  std::size_t input =
    getResponseIndex(inputManager_, binaryOptions.size());

  return (input == 0);
}



bool
Engine::createActor()
{
  if (!inDevMode_) return false;

  if (promptBinaryOption("Create an actor?")) {
    std::cout << "Actor name:\n";
    std::string actorName = inputManager_.promptClean();
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



Engine::FullOptionList&
Engine::currentOptions()
{
  return stateOptions_[state_];
}



bool
Engine::toLobby(int nextId)
{
  if (nextId == 0) {
    state_ = LOBBY;
    return true;
  }

  else return false;
}



void
Engine::loadRoot()
{
  std::string rootFileName = "root.txt";
  assert(dep::checkFileExists(rootFileName));

  getline(std::ifstream { rootFileName }, rootPath_);
}



std::string
Engine::fromRoot(std::string path) const
{
  return rootPath_ + path;
}


}
