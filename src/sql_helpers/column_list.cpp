#include "column_list.h"

#include <utility>
#include <limits>
#include <mutex>
    
namespace {  // Support

using namespace tbe::sql;

ColumnListIdSizeType
genColumnListId()
{
  // The maximum number that currentId can reach before an exception is thrown.
  static size_t maxCount =
    std::numeric_limits<ColumnListIdSizeType>::max();

  static std::mutex currentIdMutex;
  static ColumnListIdSizeType currentId = 0;

  std::lock_guard<std::mutex> guard(currentIdMutex);
  if (currentId >= maxCount)
    throw std::runtime_error("ColumnList maximum id reached");

  ++currentId;

  return currentId;
}

} // Support



namespace tbe {
  namespace sql {

void
swap(ColumnList& first, ColumnList& second)
{
  using std::swap;

  first.columns_.swap(second.columns_);
}



ColumnList::ColumnList(ColumnListId id) :
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