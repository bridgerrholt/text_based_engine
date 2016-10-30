/// @file text.h
/// Declaration of the template instantiation typedef tbe::sql::types::Text.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_TEXT_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_TEXT_H

#include <string>

#include "basic_type.h"

namespace tbe {
  namespace dev_tools {
    namespace types {
      
/// @typedef BasicType<std::string> Text
/// BasicType instantiation representing an SQL text value.
using Text = BasicType<std::string>;

    }
  }
}

#endif