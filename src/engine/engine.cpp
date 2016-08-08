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

#include "../sql_support/types/include.h"
#include "../sql_support/dynamic_query.h"
#include "../sql_support/query_object.h"
#include "../sql_support/column_list.h"

#include "../sql_support/where_clause/expression.h"
#include "../sql_support/where_clause/where_clause.h"

#include "database_structure.h"
#include "ask_question.h"
#include "run_info.h"

namespace {

using namespace tbe::sql;

Tables              tables;
Tables::Actors    & actors    = tables.actors;
Tables::Responses & responses = tables.responses;
Tables::Options   & options   = tables.options;

}



namespace tbe {

using namespace tbe::sql;

Engine::Engine() :
  Engine(std::locale())
{

}


Engine::Engine(std::locale locale) :
  locale_(std::move(locale)),
  inputManager_(locale_),
  commandProcessor_(locale_, stateMap_)
{
  using namespace commands;

  dep::printLineErr("Engine constructor called");

  loadRoot();

  /*stateOptions_[BAD];
  stateOptions_[LOBBY] = {{}, 0};
  stateOptions_[PLAYER_RESPONSE] = {{}, 1};*/
  
  commandProcessor_.pushCommandState(BAD, { QUIT });
  commandProcessor_.pushCommandState(LOBBY, {});
  commandProcessor_.pushCommandState(PLAYER_RESPONSE, {});

  stateMap_.insertGlobalVar<types::Bool>("dev",     false);
  stateMap_.insertGlobalVar<types::Bool>("to_quit", false);

  commandProcessor_.readCommandV2("hey there");

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
  database_ = DatabaseHandle(fileName);
  
  ColumnList columns ({
    &::actors.name,
    &::actors.introId
  });

  for (auto & i : actors_) {
    std::cerr << i.col(::actors.name)    << ' ' <<
                 i.col(::actors.introId) << '\n';
  }
  
  DynamicQuery dyQ { *database_, "actors", columns };

  actors_ = dyQ.run();
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
  using namespace commands;

  if (toQuit) return;

  // Used to define the columns for all the queries, it is cleared every
  // time it passes its data to a query.
  ColumnList columns;


  // Columns for the "actors" query.
  columns.push({
    &::actors.name,
    &::actors.introId
  });
  
  // The contents of columns is swapped out with a fresh ColumnList.
  DynamicQuery actorQuery { *database_, "actors", columns };


  // Columns for the "options" query.
  columns.push({
    &::options.id,
    &::options.characterId,
    &::options.optionListId,
    &::options.textDisplay,
    &::options.textSpeak,
    &::options.nextId
  });

  // Only 1 specific option list is pulled at a time, based on its unique id.
  std::unique_ptr<Expression> idExpression {
    new Expression(::options.optionListId, "=", "")
  };
  
  // Since only the pointers are passed around (no other data is moved),
  // it's safe to reference values. This is faster and simpler than dynamically casting the
  // expression back every time it needs to be accessed.
  std::string & nextOptionList = idExpression->valueText;

  WhereClause::ExpressionType
    idExpressionGeneric { std::move(idExpression) };

  std::string optionTable = "options";
  sql::DynamicQuery optionQuery { *database_, optionTable, columns,
    std::unique_ptr<WhereClauseBase>(
      new WhereClause(std::move(idExpressionGeneric))
    )
  };


  // Columns for the "responses" query.
  columns.push({
    &::responses.id,
    &::responses.textSpeak,
    &::responses.nextId
  });

  // Only 1 response is pulled at a time.
  idExpression.reset(new Expression(::responses.id, "=", ""));
  
  std::string & nextResponse = idExpression->valueText;

  idExpressionGeneric = std::move(idExpression);

  sql::DynamicQuery responseQuery { *database_, "responses", columns,
    std::unique_ptr<WhereClauseBase>(
      new WhereClause(std::move(idExpressionGeneric))
    )
  };



  actors_ = actorQuery.run();

  state_ = LOBBY;

  QueryObject * currentActor { 0 };

  QueryResult optionLists;

  // The ID of the next actor response.
  int next { 0 };
  
  // Initialized before the main loop and resized in the lobby.
  ResponseOptionList primaryOptions;

  // Specifies how many options always remain while in the lobby.
  // primaryOptions is resized to it in the lobby in case actors change.
  const std::size_t constantOptionsCount { 1 };

  stateOptions_[LOBBY].optionList.push_back("QUIT"); // Breaks out of the main loop.

  while (state_ != BAD) {
    bool toExit { false };
    
    // Printed after printing the options.
    std::string postText { };

    // First processing.
    switch (state_) {
      case LOBBY :
        // Exit the function if the database doesn't contain any actors.
        if (actors_.size() == 0) {
          dep::printLine("Nobody seems to be around.");

          if (createActor()) {
            actors_ = actorQuery.run();
            continue;
          }

          toExit = true;
          break;
        }
        else {
          // All the old actors are removed and all the current actors are added.
          stateOptions_[LOBBY].optionList.resize(constantOptionsCount);
          for (auto & i : actors_)
            stateOptions_[LOBBY].optionList.push_back(i.col(actors.name));

          postText = "Who would you like to talk to?";
        }

        break;

      case PLAYER_RESPONSE :
      {
        // The conversation is ongoing until one of the actions points to the ID of 0.
        if (toLobby(next)) continue;

        nextResponse = std::to_string(next);

        QueryResult responseList = responseQuery.run();

        // Fail if there isn't exactly 1 response with the given id.
        if (responseList.size() != 1) {
          std::string errorMessage;

          if (responseList.size() == 0)
            errorMessage = "No response";
          else
            errorMessage = "Multiple responses";

          throw std::runtime_error(
            errorMessage + " with the id of " + nextResponse
          );
        }

        QueryObject response = std::move(responseList[0]);
        std::cerr << response.varList.size() << '\n';

        // Outputs the actor's dialogue and sleeps.
        // %name%: %textSpeak%-sleep-
        std::cout << '\n' <<
          currentActor->col(::actors.name) << ": " <<
          response.col(::responses.textSpeak) << sleepEvent_ << '\n';

        int nextOptionListId { response.col(::responses.nextId) };

        std::cerr << "Response: " << nextOptionListId << '\n';

        // The conversation is over if the next ID is marked as 0.
        if (toLobby(nextOptionListId)) continue;


        nextOptionList = std::to_string(nextOptionListId);

        optionLists = optionQuery.run();

        if (optionLists.size() == 0) {
          throw std::runtime_error(
            "No option list (within table \"" + optionTable +
            "\") with the id of " + nextOptionList
          );
        }

        std::cerr << "Got options\n";

        // Lists all the textDisplay strings from the options.
        currentOptions().optionList.clear();
        for (auto & i : optionLists)
          currentOptions().optionList.push_back(i.col(::options.textDisplay));
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
    RunInfo command;
    std::size_t optionIndex { 0 };

    // Gets the player input.
    while (true) {
      if (getInputCommand(command, inputString)) {
        isCommand = (command.kind != NO_COMMAND);
      }

      else {
        if (processResponseIndex(inputString, currentOptions().optionList.size(),
                                 optionIndex, currentOptions().startNum))
        {
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
          // All the constant options are handled.
          // QUIT
          if (optionIndex == 0) {
            toExit = true;
            break;
          }

          // The actor index must be offset backwards from the constant option offset.
          // In other words, to map the optionIndex to the actors_ list, the amount of
          // non-actor options must be subtracted.
          currentActor = &actors_[optionIndex-constantOptionsCount];

          // The ID of the next actor response.
          next = currentActor->col(actors.introId);
          std::cerr << next << '\n';

          // If the intro ID is 0, that indicates no conversation will take place.
          if (next == 0) {
            std::cout << currentActor->col(actors.name) <<
              " doesn't want to speak right now.\n";

            // Stays in the lobby.
            break;
          }
          else {
            state_ = PLAYER_RESPONSE;
            std::cerr << "Wants to speak\n";
          }

          break;

        case PLAYER_RESPONSE :
          std::cerr << "PLAYER_RESPONSE\n";
          // Displays the user's response and sleeps.
          std::cout << '\n' <<
            optionLists[optionIndex].col(::options.textSpeak) << '\n' <<
            sleepEvent_;

          next = optionLists[optionIndex].col(::options.nextId);
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
  using namespace commands;

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
      RunInfo     command;

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

  database_ = DatabaseHandle(fileName);
  return true;
}



void
Engine::createDatabase(std::string const & fileName)
{
  database_ = DatabaseHandle(fileName);

  std::ifstream file { fromRoot("table_signatures.txt") };

  std::string frontText { "CREATE TABLE IF NOT EXISTS " };

  char        c;
  std::string toPush      { frontText };
  bool        hasContents { false };

  while (file >> std::noskipws >> c) {
    if (!hasContents && std::isspace(c, locale_))
      continue;
    
    toPush += c;
    hasContents = true;

    if (c == ';') {
      std::cerr << "toPush: " << toPush << '\n';
      Query query {
        *database_,
         toPush
      };
      query.nextRow();
      toPush.erase(toPush.begin() + frontText.size(), toPush.end());
      hasContents = false;
    }
  }
}



bool
Engine::getInputCommand(RunInfo & command,
                        std::string & input)
{
  input = inputManager_.promptClean();
  std::cerr << "getInputCommand: " << input << '\n';

  if (input.empty())
    return true;

  command = commandProcessor_.readCommandV2(input);

  switch (command.state) {
    case RunInfo::NONE :
      return false;

    case RunInfo::VALID :
      processGenericCommand(command);
  
      return true;

    case RunInfo::INVALID :
      std::cout << "No such command\n";
      return true;

    default :
      throw std::runtime_error("Invalid CommandProcessor::InputInfo");
  }
}


void
Engine::processGenericCommand(RunInfo const & command)
{
  using namespace commands;

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

    Query countQuery { *database_, "SELECT COUNT(*) FROM actors" };
    countQuery.nextRow();
    introId = sqlite3_column_int(countQuery.getHandle(), 0);

    std::cerr << "actorName: " << actorName << '\n';
    std::cerr << "introId:   " << introId << '\n';

    std::string text {
      "INSERT INTO actors (name, intro_id) VALUES ('" +
       actorName + "', " +
       std::to_string(introId) + ");"
    };

    Query query {
      *database_, text
    };

    query.nextRow();

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
