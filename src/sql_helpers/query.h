#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_H

#include <vector>

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

    ~Query();

    bool nextRow();
    void verifyColumnCount(int desiredCount);

    std::string readString(int columnIndex);

    sqlite3_stmt* getHandle() const;

  private:
    sqlite3_stmt* handle_;
    int rowId;
};

  }
}

#endif