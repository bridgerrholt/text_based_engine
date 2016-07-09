/// @file query_object.h
/// Declaration of the class tbe::sql::QueryObject.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_QUERY_OBJECT_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_QUERY_OBJECT_H

#include <dep/of_dynamic.h>

#include "types/include.h"

#include "column_info/basic_column_info.h"

#include "common/var_list.h"

namespace tbe {
  namespace sql {

class QueryObject
{
  public:
    /// Friend because of private variables.
    friend
    void swap(QueryObject& first, QueryObject& second);

    /// Primary constructor.
    /// columnListId Copied into @ref columnListId_.
    QueryObject(std::size_t columnListId);

    /// Move constructor.
    /// The copy constructor is deleted because of @ref varList.
    QueryObject(QueryObject && other);

    /// Returns an underlying column.
    ///
    /// @tparam The type to cast the column to.
    /// @param column Used to identify which column to return.
    /// @return Reference to the underlying column.
    template <class T>
    T const & getCol(ColumnInfo const & column);

    types::Int ::DataType col(types::col::Int  const & column);
    types::Text::DataType col(types::col::Text const & column);

    /// The list of values.
    VarList varList;

  private:
    /// The id of the column used for mapping within the column retrieval functions.
    std::size_t columnListId_;
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