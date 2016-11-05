/// @file object.h
/// Definition of the tbe::dev_tools::argument::BasicArgument alias tbe::dev_tools::argument::Object.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_COMMON_OBJECT_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_COMMON_OBJECT_H

#include "../basic_argument.h"

namespace tbe {
	namespace dev_tools {
		namespace argument {


using Object = BasicArgument<ArgumentTypeId::OBJECT>;


		}
	}
}

#endif