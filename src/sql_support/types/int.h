/// @file int.h
/// Declaration of the template instantiation typedef tbe::sql::types::Int.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_INT_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_INT_H

#include "basic_type.h"

namespace tbe {
  namespace sql {
    namespace types {
      
/// @typedef BasicType<int, INT> Int
/// BasicType instantiation representing an SQL int value.
typedef BasicType<int, INT> Int;

    }
  }
}

#endif