/// @file query_data.h
/// Declaration of the tbe::sql::QueryDataCore and tbe::sql::QueryDataFull classes.

// TODO: Remove QueryData and its associated classes. New classes are much better.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_QUERY_DATA_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_QUERY_DATA_H

#include <string>

#include <sqlite3.h>

namespace tbe {
  namespace sql {

/// The incomplete information for a query.
class QueryDataCore
{
  public:
    QueryDataCore(sqlite3* database);

    QueryDataCore(
      sqlite3*    database,
      std::string whereClause);

    sqlite3* getDatabase() const;

    void changeWhereClause(std::string newWhereClause);


  protected:
    sqlite3*    database_;

    std::string whereClause_;

    bool hasWhereClause_;
};



/// All the information needed for a query.
class QueryDataFull : public QueryDataCore
{
  public:
    QueryDataFull(
      QueryDataCore queryData,
      std::string   selectClause = "*");

    QueryDataFull(
      sqlite3*    database,
      std::string selectClause = "*");

    QueryDataFull(
      sqlite3*    database,
      std::string selectClause,
      std::string whereClause);

    std::string formatQueryText(std::string const & tableName) const;


  private:
    std::string selectClause_;
};



  }
}

#endif