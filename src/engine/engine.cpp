/// @file engine.cpp
/// Definition of the class tbe::Engine.

#include "engine.h"

#include <iostream>
#include <stdexcept>
#include <cassert>

#include <dep/check_file_exists.h>
#include <dep/is_int.h>
#include <dep/of_dynamic.h>
#include <dep/sleep_event.h>

#include "../sql_support/types/include.h"
#include "../sql_support/dynamic_query.h"
#include "../sql_support/query_object.h"
#include "../sql_support/column_list.h"

#include "../sql_support/where_clause/expression.h"
#include "../sql_support/where_clause/where_clause.h"

#include "database_structure.h"
#include "ask_question.h"

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


Engine::Engine(std::locale const & locale) :
  locale_(locale),
  inputManager_(locale_)
{

}



Engine::~Engine()
{
  // Any member queries should be closed before the database is closed.

  closeDatabase();

  std::cerr << "Engine destructed\n";
}



void
Engine::loadDatabase(std::string const & fileName)
{
  openDatabase(fileName);
  
  ColumnList columns ({
    &::actors.name,
    &::actors.introId
  });

  for (auto & i : actors_) {
    std::cerr << i.col(::actors.name)    << ' ' <<
                 i.col(::actors.introId) << '\n';
  }
  
  DynamicQuery dyQ { database_, "actors", columns };

  actors_ = dyQ.run();
}



void
Engine::run()
{
  // Exit the function if the database doesn't contain any actors.
  std::size_t actorCount = actors_.size();
  if (actorCount == 0) {
    std::cout << "Nobody seems to be around.\n";
    return;
  }
  
  // Columns for the "options" query.
  sql::ColumnList columns({
    &::options.id,
    &::options.characterId,
    &::options.optionListId,
    &::options.textDisplay,
    &::options.textSpeak,
    &::options.nextId
  });

  std::unique_ptr<Expression> idExpression (
    new Expression(::options.optionListId, "=", "")
  );

  std::string & nextOptionList = idExpression->valueText;

  WhereClause::ExpressionType idExpressionDynamic(
    std::move(idExpression)
  );



  // Swaps out columns contents.
  std::string optionTable = "options";
  sql::DynamicQuery optionQuery(database_, std::string(optionTable), columns,
    std::unique_ptr<WhereClauseBase>(
      new WhereClause(std::move(idExpressionDynamic))
    )
  );

  
  // Columns for the "responses" query.
  columns.push({
    &::responses.id,
    &::responses.textSpeak,
    &::responses.nextId
  });

  // Only 1 specific response is pulled at a time, based on its unique id.
  idExpression.reset(new Expression(::responses.id, "=", ""));
  
  // Since only the pointers are passed around (no other data is moved),
  // it's safe to reference values. This is faster and simpler than dynamically casting the
  // expression back every time it needs to be accessed.
  std::string & nextResponse = idExpression->valueText;

  idExpressionDynamic = std::move(idExpression);


  sql::DynamicQuery responseQuery(database_, "responses", columns,
    std::unique_ptr<WhereClauseBase>(
      new WhereClause(std::move(idExpressionDynamic))
    )
  );


  // Initialized before the main loop and resized every iteration.
  std::vector<std::string> primaryOptions;

  // Specifies how many options remain through every iteration,
  // primaryOptions is resized to it every iteration in case actors change.
  const std::size_t constantOptionsCount = 1;

  primaryOptions.push_back("QUIT"); // Breaks out of the main loop.

  // The main game loop.
  // Upon every iteration it shows the list of actors and lets the player talk to one.
  while (true) {
    // All the old actors are removed and all the current actors are added.
    primaryOptions.resize(constantOptionsCount);
    for (auto & i : actors_)
      primaryOptions.push_back(i.col(actors.name));

    // The player selects an index of primaryOptions.
    std::size_t optionIndex =
      askQuestion(inputManager_, primaryOptions,
                 "Who would you like to talk to?", 0);

    // All the constant options are handled.
    // QUIT
    if (optionIndex == 0) break;

    // The actor index must be offset backwards from the constant option offset.
    // In other words, to map the optionIndex to the actors_ list, the amount of
    // non-actor options must be subtracted.
    QueryObject& currentActor = actors_[optionIndex-constantOptionsCount];

    // The ID of the next actor response.
    int next { currentActor.col(actors.introId) };
    std::cerr << next << '\n';

    // If the intro ID is 0, that indicates no conversation will take place.
    if (next == 0) {
      std::cout << currentActor.col(actors.name) <<
        " doesn't want to speak right now.\n";

      // Skips the upcoming loop, bringing back the options menu.
      continue;
    }

    std::cerr << "Wants to speak\n";

    // The conversation is ongoing until one of the actions points to the ID of 0.
    while (next != 0) {

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
        currentActor.col(::actors.name) << ": " <<
        response.col(::responses.textSpeak) << sleepEvent_ << '\n';

      int nextOptionListId { response.col(::responses.nextId) };

      std::cerr << "Response: " << nextOptionListId << '\n';

      // The conversation is over if the next ID is marked as 0.
      if (nextOptionListId == 0)
        break;


      nextOptionList = std::to_string(nextOptionListId);

      QueryResult optionLists = optionQuery.run();

      if (optionLists.size() == 0) {
        throw std::runtime_error(
          "No option list (within table \"" + optionTable +
          "\") with the id of " + nextOptionList
        );
      }

      std::cerr << "Got options\n";

      // Lists all the textDisplay strings from the options.
      std::vector<std::string> optionTextList;
      for (auto & i : optionLists)
        optionTextList.push_back(i.col(::options.textDisplay));
      std::cerr << "Option text list\n";

      // Prompts the user for their text option selection.
      optionIndex = askQuestion(inputManager_, optionTextList);

      // Displays the user's response and sleeps.
      std::cout << '\n' <<
        optionLists[optionIndex].col(::options.textSpeak) << '\n' <<
        sleepEvent_;

      next = optionLists[optionIndex].col(::options.nextId);

    } // Conversation
  } // Actor selection
}


void
Engine::run(std::string const & fileName)
{
  loadDatabase(fileName);
  run();
}



void
Engine::openDatabase(std::string const & fileName)
{
  // Closes the database if it's open.
  closeDatabase();

  // Specifically check if the user's provided database file path doesn't exist.
  if (!dep::checkFileExists(fileName)) {
    throw std::runtime_error(
      "Database file can't be found:\n " + fileName
    );
  }

  // Attempts to open the database.
  int resultCode = sqlite3_open_v2(
    fileName.c_str(), &database_,
    SQLITE_OPEN_READWRITE, 0
  );

  if (resultCode != SQLITE_OK) {
    // Resources must be freed even on failure.
    sqlite3_close(database_);

    throw std::runtime_error(
      "Can't open database:\n " +
        fileName + "\n"
      "because:\n" +
       sqlite3_errmsg(database_)
    );
  }

  // Database was opened successfully.
  else databaseOpened_ = true;
}



void
Engine::closeDatabase()
{
  // Only attempt to close if it was opened.
  // Terrible problems arise from freeing unallocated memory even with sqlite3 functions.
  if (databaseOpened_) {
    std::cerr << "About to close opened database\n";

    // Shouldn't be anything but SQLITE_OK.
    if (sqlite3_close_v2(database_) != SQLITE_OK) {
      std::cerr << "Database couldn't close\n";
    }
    else {
      std::cerr << "Closed database\n";
    }
  }

  // A database may be opened again later.
  databaseOpened_ = false;
}



}
