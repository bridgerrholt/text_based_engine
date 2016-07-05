/** @file dynamic_query.h
    Declaration of the tbe::sql::DynamicQuery class.

    @class tbe::sql::DynamicQuery
    Manages information about an SQLite query, along with a tbe::sql::Query object.
    From construction onward, the query is always gauranteed to be working as long as
    no exceptions are thrown
*/

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_DYNAMIC_QUERY_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_DYNAMIC_QUERY_H

#include <vector>
#include <memory>

#include "query.h"
#include "query_object.h"
#include "column_list.h"

#include "where_clause.h"

namespace tbe {
  namespace sql {

class DynamicQuery
{
  public:
    typedef std::vector<QueryObject> QueryResult;

    typedef std::unique_ptr<WhereClauseBase> WhereClauseType;

    /** Primary constructor.
        @param[in] database      Copied into @ref database_.
        @param[in] tableName     Swapped into @ref tableName_.
        @param[in] selectColumns Swapped into @ref selectColumns_.
        @param[in] whereClause   Moved into @ref whereClause_.
    */
    DynamicQuery(sqlite3       * database,
                 std::string   & tableName,
                 ColumnList    & selectColumns,
                 WhereClauseType whereClause =
                  WhereClauseType(new WhereClause()));
    
    std::string generateQueryText();

    /// Runs the contained query.
    /// Compiles the query if necessary.
    QueryResult run();

    /// Compiles the query if necessary.
    void compile();

    /// Sets tableName_ and recompiles.
    /// @param[in] tableName Swapped with @ref tableName_.
    void setTableName(std::string & tableName);
    std::string const & getTableName() const
      { return tableName_; }

    /// Sets selectColumns_ and recompiles.
    /// @param[in] selectColumns Swapped into @ref selectColumns_.
    void setSelectColumns(ColumnList & selectColumns);
    ColumnList const & getSelectColumns() const
      { return selectColumns_; }

  private:
    /// Swaps out the passed arguments and generated the query text.
    std::string swapGen(std::string     & tableName,
                        ColumnList      & selectColumns,
                        WhereClauseType & whereClause);

    /// Compiles without checking if mustCompile_ is true.
    void rawCompile();

    sqlite3 * database_;

    std::string     tableName_;
    ColumnList      selectColumns_;
    WhereClauseType whereClause_;

    Query query_;
    bool mustCompile_;
};

  }
}

#endif