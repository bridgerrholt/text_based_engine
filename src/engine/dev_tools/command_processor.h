/// @file command_processor.h
/// Declarations of the class tbe::dev_tools::CommandProcessor.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMAND_PROCESSOR_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMAND_PROCESSOR_H

#include <locale>
#include <string>
#include <unordered_map>
#include <functional>

#include <stdexcept>
#include <cassert>

#include <dep/string_formatter.h>

#include "commands/command_id.h"
#include "commands/commands.h"
#include "state_map.h"

#include "run_info.h"

namespace tbe {
	namespace dev_tools {


class CommandProcessor
{
	public:
		using CommandState    = std::vector       <commands::CommandId>;
		using CommandStateMap = std::unordered_map<std::size_t, CommandState>;


		CommandProcessor();

		CommandProcessor(StateMap::VariableMap sharedVariables,
		                 StateMap::VariableMap globalVariables);

		/*
		/// Attempts to read the given line.
		/// @return The command.
		commands::CommandId readCommand(std::string commandText);

		/// @return Info about what the user inputted.
		RunInfo::State readCommand(std::string     commandText,
		                           commands::CommandId& command);*/

		RunInfo readCommandV2(std::string commandText);

		void setCommandLeader(std::string commandLeader);

		/* void pushCommandState(
		typename
		CommandStateMap::key_type key,
		CommandState commandState);

		void setCurrentCommandState(
			typename
			CommandStateMap::key_type currentCommandState);*/

		StateMap & getStateMap() { return stateMap_; }


	private:
		/// Must be at the front of a command.
		std::string commandLeader_ { ":" };

		StateMap stateMap_;
};


	}
}

#endif