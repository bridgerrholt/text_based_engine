#include "query.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

#include <dep/ptr_to_string.h>

#include "query_data.h"

#include "objects/actor.h"

namespace tbe {
  namespace sql {

// Query
Query::Query(sqlite3* database, com::StringRef queryText) :
  handle_(0)
{
  char const   * tail;
  sqlite3_stmt * tempHandle;

  int returnCode = sqlite3_prepare_v2(database, queryText.c_str(), -1,
    &tempHandle, &tail);

  handle_ = std::make_shared<HandleWrapper>(tempHandle);

  if (returnCode != SQLITE_OK || getHandle() == 0) {
    throw std::runtime_error(
      "Preparation of the following query failed "
      "in sql::Query construction:\n" + queryText);
  }
}



Query::Query(QueryDataFull const & queryData,
  com::StringRef tableName) :

  Query(queryData.getDatabase(), queryData.formatQueryText(tableName))
{

}



bool
Query::nextRow()
{
  int returnCode = sqlite3_step(getHandle());

  std::stringstream exceptionMessage;
  switch (returnCode) {
    case SQLITE_DONE :
      return false;

    case SQLITE_ROW :
      return true;
      break;

    case SQLITE_BUSY :
      throw std::runtime_error("Handle (" + dep::ptrToString(getHandle()) +
        ") is busy");
      break;

    default:
      throw std::runtime_error("Handle (" + dep::ptrToString(getHandle()) +
        ") has an error (error code " + std::to_string(returnCode) + ")");
      break;
  }

  return false;
}



void
Query::verifyColumnCount(int desiredCount)
{
  if (sqlite3_column_count(getHandle()) != desiredCount) {
    throw std::runtime_error("Handle");
  }
}



std::string
Query::readString(int columnIndex)
{
  return (reinterpret_cast<char const *>(
    sqlite3_column_text(getHandle(), columnIndex)));
}



sqlite3_stmt*
Query::getHandle() const
{
  return handle_->handle;
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

  if (returnCode != SQLITE_OK) {
    std::cerr << "Finalizing not OK\n";
  }

  std::cerr << "Finalized handle\n";
}



  }
}