/// @file commands.h
/// Declarations of the command classes.

#ifndef TEXT_BASED_ENGINE_ENGINE_COMMANDS_COMMANDS_H
#define TEXT_BASED_ENGINE_ENGINE_COMMANDS_COMMANDS_H

#include <dep/of_dynamic.h>

#include "../command.h"
#include "../../argument.h"
#include "../run_info.h"
#include "kind.h"
#include "../state_map.h"

namespace tbe {
	namespace dev_tools {
		namespace commands {


template <Kind c>
class BasicCommand : public CommandBase
{
	public:
		BasicCommand() {};
		~BasicCommand() {};

		Kind getKind() const { return c; }

		CommandBase::Signature const &
			getSignature() const { return signature_; }

	private:
		RunInfo::State execute(ExecutionArgs data);

		static CommandBase::Signature signature_;
};


typedef BasicCommand<SET>        Set;
typedef BasicCommand<LIST_PATHS> ListPaths;


		}
	}
}

#endif