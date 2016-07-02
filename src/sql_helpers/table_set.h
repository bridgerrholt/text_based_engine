#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_TABLE_SET_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_TABLE_SET_H

#include <memory>

#include "column_list.h"

namespace tbe {
  namespace sql {

class TableSet
{
  public:
    TableSet();

    ColumnList assignColumnList(UnassignedColumnList& columnList);

  private:
    std::size_t currentColumnListId_ = 0;


};

  }
}

#endif