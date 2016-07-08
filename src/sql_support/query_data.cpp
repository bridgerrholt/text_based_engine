/// @file query_data.cpp

#include "query_data.h"

#include <utility> // std::move

namespace tbe {
  namespace sql {

// QueryDataCore

QueryDataCore::QueryDataCore(sqlite3* database) :
  database_(database),

  hasWhereClause_(false)
{

}


QueryDataCore::QueryDataCore(sqlite3*    database,
                             std::string whereClause) :

  database_(database),

  whereClause_(std::move(whereClause)),

  hasWhereClause_(true)
{

}



sqlite3*
QueryDataCore::getDatabase() const
{
  return database_;
}



void
QueryDataCore::changeWhereClause(std::string newWhereClause)
{
  whereClause_ = std::move(newWhereClause);
}




// QueryDataFull

QueryDataFull::QueryDataFull(QueryDataCore queryData,
                             std::string   selectClause) :

  QueryDataCore(queryData)
{
  selectClause_ = std::move(selectClause);
}


QueryDataFull::QueryDataFull(sqlite3*    database,
                             std::string selectClause) :

  QueryDataCore(database)
{
  selectClause_ = std::move(selectClause);
}


QueryDataFull::QueryDataFull(sqlite3*    database,
                             std::string selectClause,
                             std::string whereClause) :

  QueryDataCore(database, std::move(whereClause))
{
  selectClause_ = std::move(selectClause);
}



std::string
QueryDataFull::formatQueryText(std::string const & tableName) const
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