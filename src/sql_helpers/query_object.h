#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_OBJECT_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_OBJECT_H

#include <dep/of_dynamic.h>

#include "types/include.h"

#include "column_info.h"

#include "var_list.h"

namespace tbe {
  namespace sql {

class QueryObject
{
  public:
    friend
    void swap(QueryObject& first, QueryObject& second);

    QueryObject(size_t columnListId);

    QueryObject(QueryObject && other);

    template <class T>
    T const & getCol(ColumnInfo const & column);

    types::Int ::DataType col(types::col::Int  const & column);
    types::Text::DataType col(types::col::Text const & column);

    VarList varList;

  private:
    size_t columnListId_;
};



template <class T>
T const &
QueryObject::getCol(ColumnInfo const & column)
{
  return *dep::ofDynamic<T>(*(varList.at(column.getId(columnListId_))));
}



  }
}

#endif