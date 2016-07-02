/** @file dynamic_query.h
    Declaration of the tbe::sql::DynamicQuery class.

    @class tbe::sql::Query
    Manages a query handle (sqlite3_stmt) and provides methods for execution.
*/

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_DYNAMIC_QUERY_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_DYNAMIC_QUERY_H

#include <vector>
#include <memory>

#include "query.h"
#include "column_list.h"

namespace tbe {
  namespace sql {

class WhereClause {};

class DynamicQuery
{
  public:
    class Data
    {
      public:
        WhereClause whereClause;
        std::string tableName;
    };

    /// Primary constructor, both arguments are swapped out.
    DynamicQuery(Data       & data,
                 ColumnList & selectColumns);

    std::string generateQueryText();

  private:
    Data       data_;
    ColumnList selectColumns_;
};

  }
}

#endif