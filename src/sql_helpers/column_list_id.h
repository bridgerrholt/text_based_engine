#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_LIST_ID_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_LIST_ID_H

#include <dep/const_value_key.h>

namespace tbe {
  namespace sql {

class   ColumnList;
typedef size_t ColumnListIdSizeType;
typedef dep::ConstValueKey<ColumnList, ColumnListIdSizeType> ColumnListId;

  }
}

#endif