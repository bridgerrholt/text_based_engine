/// @file text.h
/// Declaration of the template instantiation typedef tbe::sql::types::Text.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_TEXT_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_TEXT_H

#include <string>

#include "basic_type.h"

namespace tbe {
  namespace sql {
    namespace types {
      
/// @typedef BasicType<std::string> Text
/// BasicType instantiation representing an SQL text value.
using Text = BasicType<std::string>;

    }
  }
}

#endif