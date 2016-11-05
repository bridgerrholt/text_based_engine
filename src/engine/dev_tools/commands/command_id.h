/// @file command_id.h
/// Declaration of the enum tbe::dev_tools::commands::CommandId.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMAND_ID
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMAND_ID

namespace tbe {
	namespace dev_tools {
		namespace commands {


enum class CommandId
{
	NONE = 0,

	QUIT,  // TODO: Remove both (they are supposed to be just aliases).
	DEV_ON,

	LIST_PATHS,
	SET
};


		}
	}
}

#endif