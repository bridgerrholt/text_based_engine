#include "column_list.h"

#include <utility>
#include <limits>

namespace tbe {
  namespace sql {

void
swap(ColumnList& first, ColumnList& second)
{
  using std::swap;

  first.columns_.swap(second.columns_);
}



ColumnListIdSizeType
genColumnListId()
{
  static size_t maxCount = std::numeric_limits<ColumnListIdSizeType>::max();
  static ColumnListIdSizeType currentId = 0;

  if (currentId >= maxCount)
    throw std::runtime_error("ColumnList maximum number reached");

  ++currentId;

  return currentId;
}



ColumnList::ColumnList(ColumnListId const & id) :
  id_(id)
{

}


ColumnList::ColumnList() :
  ColumnList(genColumnListId())
{

}


ColumnList::ColumnList(ColumnInfoList& columns) :
  ColumnList()
{
  columns_.swap(columns);
}


ColumnList::ColumnList(ColumnInfoList const & columns) :
  ColumnList()
{
  columns_ = columns;
}



ColumnList::ColumnList(ColumnList&& other) :
  ColumnList(other.id_)
{
  swap(*this, other);
}



void
ColumnList::push(ColumnInfo& column)
{
  column.insertId(id_, columns_.size());
  columns_.push_back(&column);
}



  }
}