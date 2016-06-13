/** @file query.h
    Declaration of the Query class.

    @class tbe::sql::Query
    Manages a query handle (sqlite3_stmt) and provides methods for execution.
*/

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_H

#include <vector>
#include <memory>

#include <common/string_ref.h>

#include <sqlite3.h>

#include "query_data.h"

namespace tbe {
  namespace sql {

class Query
{
  public:
    Query(sqlite3* database, com::StringRef queryText);
    Query(QueryDataFull const & queryData, com::StringRef tableName);

    bool nextRow();
    void verifyColumnCount(int desiredCount);

    std::string readString(int columnIndex);

    sqlite3_stmt* getHandle() const;

  private:
    class HandleWrapper
    {
      public:
        HandleWrapper(sqlite3_stmt* handleSet);
        ~HandleWrapper();

        sqlite3_stmt& operator* ();
        sqlite3_stmt* operator->();

        sqlite3_stmt * const handle;
    };


    std::shared_ptr<HandleWrapper> handle_;
};

  }
}

#endif