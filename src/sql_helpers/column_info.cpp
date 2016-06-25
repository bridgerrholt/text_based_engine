#include "column_info.h"
#include "database_structure.h"

namespace tbe {
  namespace sql {

ColumnInfo::ColumnInfo(std::string const & nameSet,
                       DynamicType::Kind   kindSet) :
  name(nameSet),
  kind(kindSet)
{
  
}



size_t
ColumnInfo::getId(size_t columnListId) const
{
  // An exception is thrown if columnListId is not a key within idMap_.
  return idMap_.at(columnListId);
}



void
ColumnInfo::insertId(ColumnListId columnListId,
                     size_t       id)
{
  // Throw an exception if the key (columnListId) is already within idMap_.
  if (idMap_.count(columnListId.value) != 0) {
    throw std::runtime_error(
      "ColumnListId " +
      std::to_string(columnListId.value) +
      " is already mapped"
    );
  }

  idMap_[columnListId.value] = id;
}



  }
}