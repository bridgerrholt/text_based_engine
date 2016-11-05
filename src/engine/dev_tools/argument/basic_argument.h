/// @file basic_argument.h
/// Definition of the class template tbe::dev_tools::argument::BasicArgument.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_BASIC_ARGUMENT_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_BASIC_ARGUMENT_H

#include <memory>
#include <string>
#include <vector>

#include "argument_base.h"
#include "underlying_type.h"

#include "../types/object_ptr.h"

namespace tbe {
	namespace dev_tools {
		namespace argument {

/// The ArgumentTypeId is matched internally, the user cannot specify it.
template <ArgumentTypeId typeId>
class BasicArgument : public ArgumentBase
{
	public:
		using Type = typename UnderlyingType<typeId>::Type;

		BasicArgument(Type t) : ArgumentBase(typeId),
			                   data(std::move(t)) { }

	  Type data;
};


using Object = BasicArgument<ArgumentTypeId::OBJECT>;
using Option = BasicArgument<ArgumentTypeId::OPTION>;


		}
	}
}

#endif