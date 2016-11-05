/// @file argument_list.h
/// Definition of the alias tbe::dev_tools::argument::ArgumentList.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_COMMON_ARGUMENT_LIST_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_COMMON_ARGUMENT_LIST_H

#include <vector>

#include "../argument_ptr.h"

namespace tbe {
	namespace dev_tools {
		namespace argument {


using ArgumentList = std::vector<ArgumentPtr>;


		}
	}
}

#endif