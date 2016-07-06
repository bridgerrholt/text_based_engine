/** @file dynamic_query.h
    Declaration of the tbe::sql::DynamicQuery class.

    @class tbe::sql::DynamicQuery
    Manages information about an SQLite query, along with a tbe::sql::Query object.
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
        Even though it may not always be compiled, it must always have information for
        compilation, that's why these parameters are required.

        @param[in] database      Copied into @ref database_.
        @param[in] tableName     Swapped into @ref tableName_.
        @param[in] selectColumns Swapped into @ref selectColumns_.
        @param[in] whereClause   Moved into @ref whereClause_.
    */
    DynamicQuery(sqlite3       *  database,
                 std::string   && tableName,
                 ColumnList    &  selectColumns,
                 WhereClauseType  whereClause =
                   WhereClauseType(new WhereClause()));
    
    std::string generateQueryText();

    /// Compiles and executes the query.
    QueryResult run();

    /// Executes the contained query without first compiling.
    /// Throws an exception if no compiled query.
    QueryResult onlyRun();

    /// Compiles the query.
    void compile();


    /// Sets tableName_.
    /// @param[in] tableName Swapped with @ref tableName_.
    /// @return Itself so that another function can be stringed on.
    DynamicQuery& setTableName(std::string & tableName);

    std::string       & getTableName()
      { return tableName_; }
    std::string const & getTableName() const
      { return tableName_; }


    /// Sets selectColumns_.
    /// @param[in] selectColumns Swapped into @ref selectColumns_.
    /// @return Itself so that another function can be stringed on.
    DynamicQuery& setSelectColumns(ColumnList & selectColumns);

    ColumnList       & getSelectColumns()
      { return selectColumns_; }
    ColumnList const & getSelectColumns() const
      { return selectColumns_; }


    /// Sets whereClause_.
    /// @param[in] selectColumns Swapped into @ref selectColumns_.
    /// @return Itself so that another function can be stringed on.
    DynamicQuery& setWhereClause(WhereClauseType whereClause);
   
    WhereClauseBase       & getWhereClause()
      { return *whereClause_; }
    WhereClauseBase const & getWhereClause() const
      { return *whereClause_; }

  private:
    /// Swaps out the passed arguments and generated the query text.
    std::string swapGen(std::string     & tableName,
                        ColumnList      & selectColumns,
                        WhereClauseType & whereClause);

    /// Executes the query without throwing an exception if it wasn't compiled.
    QueryResult rawRun();

    sqlite3 * database_;

    std::string     tableName_;
    ColumnList      selectColumns_;
    WhereClauseType whereClause_;

    /// Uses heap allocation because it doesn't have to always be constructed.
    std::unique_ptr<Query> query_;
};

  }
}

#endif