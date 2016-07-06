#include "engine.h"

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cctype>

#include <dep/check_file_exists.h>
#include <dep/is_int.h>
#include <dep/sleep_event.h>
#include <dep/of_dynamic.h>

#include "ask_question.h"

#include "sql_helpers/mapped_query.h"
#include "sql_helpers/dynamic_query.h"
#include "sql_helpers/query_object.h"

#include "sql_helpers/types/include.h"
#include "sql_helpers/column_list.h"
#include "sql_helpers/database_structure.h"

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
  locale_(""), // Player's default locale
  inputManager_(locale_),

  databaseOpened_(false),
  database_(0),

  sleepEvent_(500)
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

  std::cerr << "First ColumnList\n";
  ColumnList columns;
  columns.push(::actors.name);
  columns.push(::actors.introId);

  MappedQuery query({database_}, "actors", columns);
  std::cerr << "ColumnList size " << columns.getColumns().size() << '\n';

  actors_ = query.run();

  for (auto & i : actors_) {
    std::cerr << i.col(::actors.name)    << ' ' <<
                 i.col(::actors.introId) << '\n';
  }
  
  columns.push(::actors.name);
  columns.push(::actors.introId);
  DynamicQuery dyQ { database_, std::string("actors"), columns };

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

  // Swaps out columns contents.
  sql::DynamicQuery optionQuery(database_, "options", columns);
  
  // Columns for the "responses" query.
  columns.push({
    &::responses.id,
    &::responses.textSpeak,
    &::responses.nextId
  });

  // Only 1 specific response is pulled at a time, based on its unique id.
  auto responsesIdExpression =
    std::unique_ptr<Expression>(new Expression(::responses.id, "=", ""));
  
  // Since only the pointers are passed around (no other data is moved),
  // it's safe to reference values. This is faster and simpler than dynamically casting the
  // expression back every time it needs to be accessed.
  std::string & responsesNext = responsesIdExpression->valueText;

  WhereClause::ExpressionType responseExpression(
    std::move(responsesIdExpression)
  );


  sql::DynamicQuery responseQuery(database_, "responses", columns,
    std::unique_ptr<WhereClauseBase>(
      new WhereClause(std::move(responseExpression))
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

    // The ID of the next row to query. It's meaning alternates from between a row in the
    // "responses" table and a row in the "options" table.
    int next = currentActor.col(actors.introId);
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

      responsesNext = std::to_string(next);

      DynamicQuery::QueryResult responseList = responseQuery.run();

      // Fail if there isn't exactly 1 response with the given id.
      if (responseList.size() != 1) {
        std::string errorMessage;

        if (responseList.size() == 0)
          errorMessage = "No response";
        else
          errorMessage = "Multiple responses";

        throw std::runtime_error(
          errorMessage + " with the id of " + responsesNext
        );
      }

      QueryObject response = std::move(responseList[0]);
      std::cerr << response.varList.size() << '\n';

      // Outputs the actor's dialogue and sleeps.
      // %name%: %textSpeak%-sleep-
      std::cout << '\n' <<
        currentActor.col(::actors.name) << ": " <<
        response.col(::responses.textSpeak) << sleepEvent_ << '\n';

      std::cerr << "Response: " << response.col(::responses.nextId) << '\n';

      // The conversation is over if the next ID is marked as 0.
      if (response.col(::responses.nextId) == 0)
        break;

      // Queries the next option list.
      sql::Option optionCall({database_,
        "option_list_id = " + std::to_string(response.col(::responses.nextId))
      });

      // Runs the query, collecting the list of options.
      std::vector<sql::Option::Data> options =
        optionCall.run();

      std::cerr << "Got options\n";

      // Lists all the textDisplay strings from the options.
      std::vector<std::string> optionTextList;
      for (auto i : options)
        optionTextList.push_back(i.textDisplay);
      std::cerr << "Option text list\n";

      // Prompts the user for their text option selection.
      std::size_t optionIndex = askQuestion(inputManager_, optionTextList);
      std::cout << '\n' <<
        options[optionIndex].textSpeak << '\n' << sleepEvent_;

      // The ID of the next actor response.
      next = options[optionIndex].nextId;

    } // Conversation
  } // Actor selection
}



void
Engine::openDatabase(std::string const & fileName)
{
  // Closes the database if it's open.
  closeDatabase();

  // Specifically pass if the user's provided database file path doesn't exist.
  if (!dep::checkFileExists(fileName)) {
    throw std::runtime_error(
      "Database file can't be found:\n " +
        fileName
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
