/// @file argument_base.h
/// Declaration of the abstract base class tbe::dev_tools::argument::ArgumentBase.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_ARGUMENT_BASE_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_ARGUMENT_BASE_H

#include "argument_type_id.h"

namespace tbe {
	namespace dev_tools {
		namespace argument {


class ArgumentBase
{
	public:
		ArgumentBase(ArgumentTypeId typeSet);

		virtual
		~ArgumentBase() = 0;

		ArgumentTypeId const type;
};


		}
	}
}

#endif