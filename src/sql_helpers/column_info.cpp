#include "column_info.h"
#include "database_structure.h"

namespace tbe {
  namespace sql {

ColumnInfoBase::ColumnInfoBase(std::string const & name,
                               DynamicType::Kind   kind) :
  name_(name),
  kind_(kind)
{

}



ColumnInfo::ColumnInfo(std::string const & name,
                       DynamicType::Kind   kind) :
  ColumnInfoBase(name, kind)
{

}



void
ColumnInfo::setId(size_t id)
{
  id_ = id;
}





ColumnInfoMapped::ColumnInfoMapped(std::string const & name,
                                   DynamicType::Kind   kind) :
  ColumnInfoBase(name, kind)
{

}



size_t
ColumnInfoMapped::getId(size_t columnListId) const
{
  return idMap_.at(columnListId);
}



void
ColumnInfoMapped::setId(size_t id, size_t columnListId)
{
  idMap_[columnListId] = id;
}



  }
}