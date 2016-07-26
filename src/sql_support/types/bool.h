/// @file bool.h
/// Declaration of the template instantiation typedef tbe::sql::types::Bool.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_BOOL_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_BOOL_H

#include "basic_type.h"

namespace tbe {
  namespace sql {
    namespace types {
      
/// @typedef BasicType<bool, BOOL> Bool
/// BasicType instantiation representing an SQL bool value.
typedef BasicType<bool, BOOL> Bool;

    }
  }
}

#endif