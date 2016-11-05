/// @file underlying_type.h
/// Definition of the class template tbe::dev_tools::argument::UnderlyingType.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_UNDERLYING_TYPE_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_ARGUMENT_UNDERLYING_TYPE_H

#include "argument_type_id.h"

#include "../types/object_ptr.h" // OBJECT
#include <string>                // OPTION

namespace tbe {
	namespace dev_tools {
		namespace argument {


// Underlying types.
template <ArgumentTypeId id>
class UnderlyingType
{
	public:
		UnderlyingType() = delete;
};


template <>
class UnderlyingType<ArgumentTypeId::OBJECT>
{
	public:
		UnderlyingType() = delete;
		using Type = types::ObjectPtr;
};


template <>
class UnderlyingType<ArgumentTypeId::OPTION>
{
	public:
		UnderlyingType() = delete;
		using Type = std::string;
};


		}
	}
}

#endif