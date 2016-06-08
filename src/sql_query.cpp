#include "sql_query.h"

#include <iostream>
#include <stdexcept>

namespace tbe {

SqlQuery::SqlQuery(sqlite3* database, com::StringRef queryText) :
  handle_(0)
{
  char const * tail;
  int returnCode = sqlite3_prepare_v2(database, queryText.c_str(), -1,
    &handle_, &tail);

  if (returnCode != SQLITE_OK || handle_ == 0) {
    throw std::runtime_error(
      "Preparation of the following query failed"
      "in SqlQuery construction:\n" + queryText);
  }
}



SqlQuery::~SqlQuery()
{
  std::cout << handle_ << '\n';
  std::cout << "Finalizing\n";
  int returnCode = sqlite3_finalize(handle_);
  if (returnCode != SQLITE_OK) {
    std::cout << "Finalizing not OK\n";
  }
}



sqlite3_stmt*
SqlQuery::getHandle() const
{
  return handle_;
}



}