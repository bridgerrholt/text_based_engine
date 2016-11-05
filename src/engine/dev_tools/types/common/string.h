/// @file string.h
/// Definition of the tbe::dev_tools::types::BasicObject alias tbe::dev_tools::types::String.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_STRING_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_STRING_H

#include <string>

#include "../basic_object.h"

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