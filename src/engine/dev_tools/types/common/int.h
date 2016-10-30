/// @file int.h
/// Declaration of the template instantiation typedef tbe::sql::types::Int.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_INT_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_INT_H

#include "basic_type.h"

namespace tbe {
  namespace dev_tools {
    namespace types {
      
/// @typedef BasicType<int> Int
/// BasicType instantiation representing an SQL int value.
using Int = BasicType<int>;

    }
  }
}

#endif