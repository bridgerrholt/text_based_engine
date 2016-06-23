#include "column_list.h"

#include <utility>

namespace tbe {
  namespace sql {

size_t
genColumnListId()
{
  static size_t currentId = 0;
  ++currentId;

  return currentId;
}



ColumnList::ColumnList() :
  id_(genColumnListId())
{

}



void
ColumnList::push(ColumnInfoMapped& column)
{
  column.setId(columns_.size(), id_);
  columns_.push_back(column);
}



  }
}