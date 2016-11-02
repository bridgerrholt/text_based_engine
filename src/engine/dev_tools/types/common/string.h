/// @file string.h
/// Declaration of the template instantiation alias tbe::sql::types::Text.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_TEXT_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_TEXT_H

#include <string>

#include "basic_object.h"

namespace tbe {
	namespace dev_tools {
		namespace types {


/// @typedef BasicObject<std::string> Text
/// BasicObject instantiation representing a string type.
using String = BasicObject<std::string>;


		}
	}
}

#endif