#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_LIST_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_LIST_H

#include <vector>

#include "column_info.h"

namespace tbe {
  namespace sql {

class ColumnList
{
  public:
    typedef std::vector<ColumnInfoMapped> ColumnInfoList;

    ColumnList();

    void push(ColumnInfoMapped& column);

    ColumnInfoList const & getColumns() const { return columns_; }
    size_t                 getId()      const { return id_; }


  private:
    ColumnInfoList columns_;

    size_t id_;
};



  }
}

#endif