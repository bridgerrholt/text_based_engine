/// @file int.h
/// Declaration of the template instantiation typedef tbe::sql::types::Int.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_INT_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_INT_H

#include "basic_object.h"

namespace tbe {
  namespace dev_tools {
    namespace types {
      
/// @typedef BasicObject<int> Int
/// BasicObject instantiation representing an SQL int value.
using Int = BasicObject<int>;

    }
  }
}

#endif