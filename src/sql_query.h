#ifndef TEXT_BASED_ENGINE_SQL_QUERY_H
#define TEXT_BASED_ENGINE_SQL_QUERY_H

#include <common/string_ref.h>

#include <sqlite3.h>

namespace tbe {

class SqlQuery
{
  public:
    SqlQuery(sqlite3* database, com::StringRef queryText);

    ~SqlQuery();
    

    sqlite3_stmt* getHandle() const;

  private:
    sqlite3_stmt* handle_;
};

}

#endif