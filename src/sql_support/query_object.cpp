/// @file query_object.cpp
/// Definition of the class tbe::sql::QueryObject.

#include "query_object.h"

#include <iostream>

namespace tbe {
  namespace sql {

using namespace types;

void
swap(QueryObject& first, QueryObject& second)
{
  using std::swap;

  first.varList.swap(second.varList);
  swap(first.columnListId_, second.columnListId_);
}



QueryObject::QueryObject(size_t columnListId) :
  columnListId_(columnListId)
{

}



QueryObject::QueryObject(QueryObject && other)
{
  swap(*this, other);
}



Int::DataType
QueryObject::col(col::Int const & column)
{
  std::cerr << "IntCol\n";
  return dep::ofDynamic<types::Int const>(*(
    varList.at(column.getId(columnListId_))
  ))->data;
}


Text::DataType
QueryObject::col(col::Text const & column)
{
  std::cerr << "TextCol\n";
  std::cerr << "at(column.getId(" << columnListId_ << "))\n";
  return dep::ofDynamic<types::Text const>(*(
    varList.at(column.getId(columnListId_))
  ))->data;
}



  }
}