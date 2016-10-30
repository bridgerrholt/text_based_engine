/// @file bool.h
/// Declaration of the template instantiation typedef tbe::sql::types::Bool.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_BOOL_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_BOOL_H

#include "basic_object.h"

namespace tbe {
  namespace dev_tools {
    namespace types {
      
/// @typedef BasicObject<bool> Bool
/// BasicObject instantiation representing an SQL bool value.
using Bool = BasicObject<bool>;

    }
  }
}

#endif