/// @file basic_command.h
/// Declaration of the class template tbe::dev_tools::commands::BasicCommand.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_BASIC_COMMAND_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_COMMANDS_BASIC_COMMAND_H

//#include <dep/of_dynamic.h>

#include "command_base.h"
//#include "../argument/argument.h"
#include "../run_info.h"
#include "command_id.h"
//#include "../state_map.h"

namespace tbe {
	namespace dev_tools {
		namespace commands {


template <CommandId c>
class BasicCommand : public CommandBase
{
	public:
		BasicCommand() {};
		~BasicCommand() {};

		CommandId getCommandId() const { return c; }

		CommandBase::Signature const &
			getSignature() const { return signature_; }

	private:
		RunInfo::State execute(ExecutionArgs data);

		static CommandBase::Signature signature_;
};


		}
	}
}

#endif