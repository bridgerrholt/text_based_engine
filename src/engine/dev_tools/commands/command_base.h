/// @file command_base.h
/// Declarations of the abstract class tbe::dev_tools::commands::CommandBase.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMAND_BASE_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_COMMAND_BASE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <locale>

#include "../types/type_id.h"

#include "command_id.h"

#include "../parameter_list.h"
#include "../argument/common/argument_list.h"
#include "../run_info.h"

namespace tbe {
	namespace dev_tools {

class StateMap;

		namespace commands {

class CommandBase
{
	public:
		class ExecutionArgPack
		{
			public:
				StateMap                                   & stateMap;
				argument::ArgumentList::const_iterator       i;
				argument::ArgumentList::const_iterator const end;
		};

		using ExecutionArgs = ExecutionArgPack;
		using Signature     = std::vector<argument::ArgumentTypeId>;


		CommandBase();

		virtual
		~CommandBase() = 0;

		RunInfo run(StateMap          & stateMap,
		            std::string const & args,
		            std::locale const & locale);


	private:
		virtual
		commands::CommandId getCommandId() const = 0;

		virtual
		RunInfo::State execute(ExecutionArgs data) = 0;

		virtual
		Signature const & getSignature() const = 0;
};


		}
	}
}

#endif