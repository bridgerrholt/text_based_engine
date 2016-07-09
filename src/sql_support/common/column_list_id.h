/// @file column_list_id.h
/// Declares the typedef tbe::sql::ColumnListId.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_COMMON_COLUMN_LIST_ID_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_COMMON_COLUMN_LIST_ID_H

#include <dep/value_key.h>

namespace tbe {
  namespace sql {

class   ColumnList;
typedef std::size_t ColumnListIdSizeType;
typedef dep::ValueKey<ColumnList, ColumnListIdSizeType> ColumnListId;

  }
}

#endif