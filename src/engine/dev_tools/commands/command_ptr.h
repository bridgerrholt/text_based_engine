/// @file command_ptr.h
/// Definition of the smart pointer tbe::dev_tools::commands::CommandPtr.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMAND_PTR_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMAND_PTR_H

#include <memory> // std::unique_ptr

#include "commands.h"

namespace tbe {
	namespace dev_tools {
		namespace commands {

/// TODO: Change back to std::unique_ptr and fix the copy problem.
using CommandPtr = std::shared_ptr<CommandBase>;

template <class T>
CommandPtr makeCommandPtr()
{
	return CommandPtr { new T() };
}

		}
	}
}

#endif