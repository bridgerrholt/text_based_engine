/// @file list_paths.h
/// Definition of the tbe::dev_tools::commands::BasicCommand alias tbe::dev_tools::commands::ListPaths.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMON_LIST_PATHS_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMON_LIST_PATHS_H

#include "../basic_command.h"

namespace tbe {
	namespace dev_tools {
		namespace commands {


using ListPaths = BasicCommand<CommandId::LIST_PATHS>;


		}
	}
}

#endif