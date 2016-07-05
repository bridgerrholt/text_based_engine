#include "query_object.h"

namespace tbe {
  namespace sql {

using namespace types;

QueryObject::QueryObject(size_t columnListId) :
  columnListId_(columnListId)
{

}



Int::DataType
QueryObject::col(col::Int const & column)
{
  return dep::ofDynamic<types::Int const>(*(
    varList.at(column.getId(columnListId_))
  ))->data;
}


Text::DataType
QueryObject::col(col::Text const & column)
{
  return dep::ofDynamic<types::Text const>(*(
    varList.at(column.getId(columnListId_))
  ))->data;
}



  }
}