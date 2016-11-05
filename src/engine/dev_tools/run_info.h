/// @file run_info.h
/// Declarations of the class tbe::dev_tools::RunInfo.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_RUN_INFO_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_RUN_INFO_H

#include "commands/command_id.h"
#include "argument/common/argument_list.h"

namespace tbe {
	namespace dev_tools {


class RunInfo
{
	public:
		enum State
		{
			NONE,
			INVALID,
			VALID
		};

		RunInfo();
		RunInfo(State                  stateSet);
		RunInfo(State                  stateSet,
		        commands::CommandId    commandIdSet,
		        argument::ArgumentList argsSet);

		State                  state;
		commands::CommandId    commandId;
		argument::ArgumentList args;
};


	}
}

#endif