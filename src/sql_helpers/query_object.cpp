#include "query_object.h"

namespace tbe {
  namespace sql {

using namespace column_info_types;

QueryObject::QueryObject(size_t columnListId) :
  columnListId_(columnListId)
{

}



types::Int::DataType
QueryObject::col(column_info_types::Int const & column)
{
  return dep::ofDynamic<types::Int>(*(
    varList.at(column.getId(columnListId_))
  ))->data;
}


types::Text::DataType
QueryObject::col(column_info_types::Text const & column)
{
  return dep::ofDynamic<types::Text>(*(
    varList.at(column.getId(columnListId_))
  ))->data;
}



  }
}