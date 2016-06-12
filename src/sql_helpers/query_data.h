#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_DATA_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_DATA_H

#include <common/string_ref.h>

#include <sqlite3.h>

namespace tbe {
  namespace sql {

class QueryDataCore
{
  public:
    QueryDataCore(sqlite3* database);

    QueryDataCore(
      sqlite3*       database,
      com::StringRef whereClause);

    sqlite3* getDatabase() const;


  protected:
    sqlite3*    database_;

    std::string whereClause_;

    bool hasWhereClause_;
};



class QueryDataFull : public QueryDataCore
{
  public:
    QueryDataFull(
      QueryDataCore  queryData,
      com::StringRef selectClause = "*");

    QueryDataFull(
      sqlite3*       database,
      com::StringRef selectClause = "*");

    QueryDataFull(
      sqlite3*       database,
      com::StringRef selectClause,
      com::StringRef whereClause);

    std::string formatQueryText(com::StringRef tableName) const;


  private:
    std::string selectClause_;
};



  }
}

#endif