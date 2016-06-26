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
      ColumnList          & selectColumns);

    QueryResult run();

    bool getColumn(com::StringRef columnName, int& id);


  private:
    std::string generateSelectClause() const;

    ColumnList selectColumns_;
    
    Query query_;

};



  }
}

#endif