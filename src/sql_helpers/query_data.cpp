#include "query_data.h"

namespace tbe {
  namespace sql {

// QueryDataCore

QueryDataCore::QueryDataCore(sqlite3* database) :
  database_(database),

  hasWhereClause_(false)
{

}


QueryDataCore::QueryDataCore(
  sqlite3*       database,
  com::StringRef whereClause) :

  database_(database),

  whereClause_(whereClause),

  hasWhereClause_(true)
{

}



sqlite3*
QueryDataCore::getDatabase() const
{
  return database_;
}



// QueryDataFull

QueryDataFull::QueryDataFull(QueryDataCore queryData,
  com::StringRef selectClause) :

  QueryDataCore(queryData)
{
  selectClause_ = selectClause;
}


QueryDataFull::QueryDataFull(
  sqlite3* database,
  com::StringRef selectClause) :

  QueryDataCore(database)
{
  selectClause_ = selectClause;
}


QueryDataFull::QueryDataFull(
  sqlite3*       database,
  com::StringRef selectClause,
  com::StringRef whereClause) :

  QueryDataCore(database, whereClause)
{
  selectClause_ = selectClause;
}



std::string
QueryDataFull::formatQueryText(com::StringRef tableName) const
{
  std::string queryText =
    "SELECT " + selectClause_ + " FROM " + tableName;

  if (hasWhereClause_)
    queryText += " WHERE " + whereClause_;

  queryText += ';';

  return queryText;
}



  }
}