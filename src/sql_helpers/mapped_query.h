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

#include <dep/of_dynamic.h>

namespace tbe {
  namespace sql {


class MappedQuery
{
  public:
    typedef std::unique_ptr<DynamicType> DynamicVar;
    typedef std::vector    <DynamicVar>  VarList;

    class QueryObject
    {
      public:
        QueryObject(size_t columnListId);

        template <class T>
        T const & getCol(ColumnInfo       const & column);

        template <class T>
        T const & getCol(ColumnInfoMapped const & column);

        VarList varList;

      private:
        size_t columnListId_;
    };

    typedef std::vector<QueryObject> QueryResult;

    class Column
    {
      public:
        std::string       name;
        DynamicType::Kind kind;
    };

    MappedQuery(
      QueryDataCore const & queryData,
      std::string   const & tableName,
      ColumnList    const & selectColumns);

    QueryResult run();

    bool getColumn(com::StringRef columnName, int& id);


  private:
    std::string generateSelectClause() const;

    ColumnList selectColumns_;
    
    Query query_;

};



template <class T>
T const &
MappedQuery::QueryObject::getCol(ColumnInfo const & column)
{
  return *dep::ofDynamic<T>(*(varList.at(column.getId())));
}


template <class T>
T const &
MappedQuery::QueryObject::getCol(ColumnInfoMapped const & column)
{
  return *dep::ofDynamic<T>(*(varList.at(column.getId(columnListId_))));
}



  }
}

#endif