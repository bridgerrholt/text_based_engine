/// @file run_info.h
/// Declarations of the class tbe::RunInfo.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_RUN_INFO_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_RUN_INFO_H

#include "commands/kind.h"
#include "../argument.h"

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
		RunInfo(State          stateSet);
		RunInfo(State          stateSet,
		        commands::Kind kindSet,
		        ArgumentList   argsSet);

		State          state;
		commands::Kind kind;
		ArgumentList   args;
};


	}
}

#endif