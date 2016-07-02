/** @file mapped_query.h
    Declaration of the tbe::sql::MappedQuery class.

    @class tbe::sql::MappedQuery
    Handles an SQL query with resulting lists mapped to specific indexes.
*/

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_MAPPED_QUERY_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_MAPPED_QUERY_H

#include <vector>
#include <unordered_map>
#include <memory>

#include <string>

#include "query.h"
#include "query_data.h"
#include "dynamic_type.h"
#include "column_list.h"
#include "column_info.h"

#include <dep/of_dynamic.h>

#include "query_object.h"

namespace tbe {
  namespace sql {

class MappedQuery
{
  public:
    /// Is returned from run().
    typedef std::vector<QueryObject> QueryResult;

    /** Primary constructor.
        All the arguments are used to construct the internal query (@ref query_).

        @param queryData Core data for the query.
        @param tableName Name of the table to be queried.
        @param selectColumns All the information for each column being queried.
                             Is moved into @ref selectColumns_.
    */
    MappedQuery(
      QueryDataCore const & queryData,
      std::string   const & tableName,
      ColumnList          & selectColumns);

    /// Runs the query.
    /// @return The list of QueryObject objects.
    QueryResult run();

    void changeWhereClause(std::string const & newWhereClause);


  private:
    /// Strings together the names of the columns within @ref selectColumns_ for the query.
    std::string generateSelectClause() const;

    /// Used for calling the right functions within run().
    ColumnList selectColumns_;
    
    QueryDataCore queryData_;

    std::string selectClause_;

    std::string tableName_;

    /// The query to be executed.
    Query query_;
};



  }
}

#endif