/// @file column_info.cpp
/// Definition of the base class tbe::sql::ColumnInfo.

#include "column_info.h"

#include <iostream>

#include "../../database_structure.h"

namespace tbe {
  namespace sql {

ColumnInfo::ColumnInfo(std::string nameSet,
                       types::Kind kindSet) :
  name(std::move(nameSet)),
  kind(kindSet)
{
  
}



std::size_t
ColumnInfo::getId(std::size_t columnListId) const
{
  std::cerr << "getId(" << columnListId << ")\n";
  for (auto i = idMap_.begin(); i != idMap_.end(); ++i) {
    std::cerr << " " << i->first << " " << i->second << '\n';
  }
  // An exception is thrown if columnListId is not a key within idMap_.
  return idMap_.at(columnListId);
}



void
ColumnInfo::insertId(ColumnListId columnListId,
                     std::size_t  id)
{
  std::cerr << "insertId(" << columnListId.get() << ", " << id << ")\n";
  // Throw an exception if the key (columnListId) is already within idMap_.
  if (idMap_.count(columnListId.get()) != 0) {
    throw std::runtime_error(
      "ColumnListId " +
      std::to_string(columnListId.get()) +
      " is already mapped"
    );
  }

  idMap_[columnListId.get()] = id;
}



  }
}