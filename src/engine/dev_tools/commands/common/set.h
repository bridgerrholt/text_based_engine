/// @file list_paths.h
/// Definition of the tbe::dev_tools::commands::BasicCommand alias tbe::dev_tools::commands::Set.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMON_SET_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMON_SET_H

#include "../basic_command.h"

namespace tbe {
	namespace dev_tools {
		namespace commands {


using Set = BasicCommand<CommandId::SET>;


		}
	}
}

#endif