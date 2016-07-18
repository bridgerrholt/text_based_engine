/// @file query.cpp
/// Definition of the class tbe::sql::Query.

#include "query.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

#include <dep/ptr_to_string.h>

namespace tbe {
  namespace sql {


std::vector<Query>
Query::createQueries(sqlite3           * database,
                     std::string const & queryText)
{
  std::cerr << "createQueries(" << database << ", " << queryText << ")\n";
  std::vector<Query> queries;

  char const * strStart = queryText.c_str();

  while (strStart != 0) {
    std::cerr << "strStart: " << strStart << '\n';
    bool containedSql;
    Query nextQuery { database, strStart, strStart, containedSql };
    std::cerr << "strTail:  " << strStart << '\n';
    std::cerr << "strTail:  " << dep::ptrToString(strStart) << '\n';
    std::cerr << "handle:   " << dep::ptrToString(nextQuery.getHandle()) << '\n';

    if (!containedSql)
      break;

    queries.push_back(std::move(nextQuery));
  }

  return queries;
}



// Query

Query::Query(sqlite3* database, std::string const & queryText)
{
  /*// The beginning of the next statement.
  // As of right now, this class does not handle queries with multiple statements.
  char const   * tail;

  // Only exists to pass the query handle to the member handle_.
  sqlite3_stmt * tempHandle;

  int returnCode = sqlite3_prepare_v2(database, queryText.c_str(), -1,
    &tempHandle, &tail);

  // Even if the query wasn't successfully made, it must be handled appropriately.
  handle_.reset(new HandleWrapper(tempHandle));

  if (returnCode != SQLITE_OK || getHandle() == 0) {
    throw std::runtime_error(
      "Preparation of the following query failed "
      "in sql::Query construction:\n" + queryText);
  }*/

  // This constructor does not handle multiple statements.
  char const * tail = 0;

  if (!coreConstruction(database, queryText.c_str(), tail)) {
    throw std::runtime_error(
      "Preparation of a query failed because the text did not contain SQL"
    );
  }
}


Query::Query(sqlite3    *   database,
             char const *   strStart,
             char const * & strTail)
{
  coreConstruction(database, strStart, strTail);
}



Query::Query(sqlite3    *   database,
             char const *   strStart,
             char const * & strTail,
             bool         & containsSql)
{
  containsSql = coreConstruction(database, strStart, strTail);
}


bool
Query::coreConstruction(
  sqlite3    *   database,
  char const *   strStart,
  char const * & strTail)
{
  // Only exists to pass the query handle to the member handle_.
  sqlite3_stmt * tempHandle = nullptr;

  int returnCode = sqlite3_prepare_v2(database, strStart, -1,
    &tempHandle, &strTail);

  // Even if the query wasn't successfully made, it must be handled appropriately.
  handle_.reset(new HandleWrapper(tempHandle));

  if (returnCode != SQLITE_OK) {
    std::string queryText;

    if (strTail == 0)
      queryText = std::string(strStart);
    else
      queryText = std::string(strStart, strTail - strStart);

    throw std::runtime_error(
      "Preparation of the following query failed "
      "in sql::Query construction:\n" + queryText);
  }

  return (getHandle() != 0);
}



bool
Query::nextRow()
{
  int returnCode = sqlite3_step(getHandle());

  if (returnCode == SQLITE_ROW)
    return true;

  else if (returnCode == SQLITE_DONE)
    return false;

  // Handles exceptions.
  else {
    std::string errorMessage = getHandleString();

    if (returnCode == SQLITE_BUSY)
      errorMessage += " is busy";

    else {
      errorMessage += " has an error (error code " +
        std::to_string(returnCode) + ")";
    }

    throw std::runtime_error(errorMessage);
  }
}



void
Query::verifyColumnCount(int desiredCount)
{
  int columnCount = sqlite3_column_count(getHandle());

  if (columnCount != desiredCount) {
    throw std::runtime_error(
      getHandleString() + " has " +
      std::to_string(columnCount)  + " column(s)"
      " instead of the desired " +
      std::to_string(desiredCount) + " column(s)"
    );
  }
}



std::string
Query::readString(int columnIndex)
{
  // Low-level format conversion. Unsure if UTF-8 but seems to work.
  return (reinterpret_cast<char const *>(
    sqlite3_column_text(getHandle(), columnIndex)));
}



sqlite3_stmt*
Query::getHandle() const
{
  return handle_->handle;
}



std::string
Query::getHandleString() const
{
  return "Handle (" + dep::ptrToString(getHandle()) + ")";
}



// Query::HandleWrapper

Query::HandleWrapper::HandleWrapper(sqlite3_stmt* handleSet) :
  handle(handleSet)
{

}



Query::HandleWrapper::~HandleWrapper()
{
  std::cerr << "Finalizing handle (" <<
    dep::ptrToString(handle) << ")\n";

  int returnCode = sqlite3_finalize(handle);

  // Using SQLite V2 functions, the data will eventually get destructed.
  if (returnCode != SQLITE_OK) {
    std::cerr << "Finalizing not OK\n";
  }

  std::cerr << "Finalized handle\n";
}



  }
}