#include "query.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

#include <dep/ptr_to_string.h>

#include "query_data.h"

#include "objects/actor.h"

namespace tbe {
  namespace sql {

Query::Query(sqlite3* database, com::StringRef queryText) :
  handle_(0)
{
  char const * tail;
  int returnCode = sqlite3_prepare_v2(database, queryText.c_str(), -1,
    &handle_, &tail);

  if (returnCode != SQLITE_OK || handle_ == 0) {
    throw std::runtime_error(
      "Preparation of the following query failed "
      "in sql::Query construction:\n" + queryText);
  }

  std::cerr << handle_ << ' ' << dep::ptrToString(handle_) << '\n';
}



Query::Query(QueryDataFull const & queryData,
  com::StringRef tableName) :

  Query(queryData.getDatabase(), queryData.formatQueryText(tableName))
{

}



Query::~Query()
{
  std::cerr << "Finalizing sql::Query (" <<
    dep::ptrToString(handle_) << ")\n";
  int returnCode = sqlite3_finalize(handle_);
  if (returnCode != SQLITE_OK) {
    std::cerr << "Finalizing not OK\n";
  }

  std::cerr << "Finalized sql::Query\n";
}



bool
Query::nextRow()
{
  int returnCode = sqlite3_step(handle_);

  std::stringstream exceptionMessage;
  switch (returnCode) {
    case SQLITE_DONE :
      return false;

    case SQLITE_ROW :
      return true;
      break;

    case SQLITE_BUSY :
      throw std::runtime_error("Handle (" + dep::ptrToString(handle_) +
        ") is busy");
      break;

    default:
      throw std::runtime_error("Handle (" + dep::ptrToString(handle_) +
        ") has an error (error code " + std::to_string(returnCode) + ")");
      break;
  }

  return false;
}



void
Query::verifyColumnCount(int desiredCount)
{
  if (sqlite3_column_count(handle_) != desiredCount) {
    throw std::runtime_error("Handle");
  }
}



std::string
Query::readString(int columnIndex)
{
  return (reinterpret_cast<char const *>(
    sqlite3_column_text(handle_, columnIndex)));
}



sqlite3_stmt*
Query::getHandle() const
{
  return handle_;
}



  }
}