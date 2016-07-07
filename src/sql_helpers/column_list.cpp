#include "column_list.h"

#include <utility>
#include <limits>
#include <mutex>
#include <iostream>

#include "column_info.h"
    
namespace {

using namespace tbe::sql;

class IdGenerator
{
  public:
    ColumnListIdSizeType generate();
    
    // The maximum number that currentId_ can reach before an exception is thrown.
    static ColumnListIdSizeType const maxCount;

  private:
    std::mutex currentIdMutex_;
    ColumnListIdSizeType currentId_ = 0;

} idGenerator;



ColumnListIdSizeType const
IdGenerator::maxCount = std::numeric_limits<ColumnListIdSizeType>::max();



ColumnListIdSizeType
IdGenerator::generate()
{
  std::lock_guard<std::mutex> guard(currentIdMutex_);
  if (currentId_ >= maxCount)
    throw std::runtime_error("ColumnList maximum id reached");

  ++currentId_;

  return currentId_;
}

}



namespace tbe {
  namespace sql {

void
swap(ColumnList& first, ColumnList& second)
{
  using std::swap;

  first.columns_.swap(second.columns_);
  swap(first.id_, second.id_);
}



ColumnList::ColumnList(ColumnListId id) :
  id_(id)
{
  std::cerr << "= " << id_.get() << '\n';
}


ColumnList::ColumnList() :
  ColumnList(idGenerator.generate())
{

}


ColumnList::ColumnList(ColumnInfoList& columns) :
  ColumnList()
{
  columns_.swap(columns);

  for (std::size_t i = 0; i < columns_.size(); ++i)
    columns_[i]->insertId(id_, i);
}


ColumnList::ColumnList(ColumnInfoList const & columns) :
  ColumnList()
{
  columns_ = columns;

  for (std::size_t i = 0; i < columns_.size(); ++i)
    columns_[i]->insertId(id_, i);
}



ColumnList::ColumnList(ColumnList&& other) :
  ColumnList()
{
  std::cerr << id_.get() << '\n';
  swap(*this, other);
}



ColumnList::~ColumnList()
{
  std::cerr << "~ " << id_.get() << '\n';
}



void
ColumnList::push(ColumnInfo& column)
{
  column.insertId(id_, columns_.size());
  columns_.push_back(&column);
}



void
ColumnList::push(std::initializer_list<ColumnInfo*> columns)
{
  std::size_t i = columns_.size();

  columns_.insert(columns_.end(), columns);

  while (i < columns_.size()) {
    columns_[i]->insertId(id_, i);

    ++i;
  }
}



std::string
ColumnList::getText()
{
  if (columns_.size() == 0)
    return "";

  std::string toReturn;

  for (std::size_t i = 0; i < columns_.size()-1; ++i) {
    toReturn += columns_[i]->name + ", ";
  }

  return toReturn + columns_.back()->name;
}



  }
}