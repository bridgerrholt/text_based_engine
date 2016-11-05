/// @file match_to_type_id.h
/// Definition of the function template tbe::dev_tools::types::matchToTypeId.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_MATCH_TO_TYPE_ID_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_MATCH_TO_TYPE_ID_H

#include <string>

#include "type_id.h"

namespace tbe {
	namespace dev_tools {
		namespace types {


template <class T>
static constexpr TypeId matchToTypeId();


template <>
constexpr TypeId
matchToTypeId<bool>() { return TypeId::BOOL; }

template <>
constexpr TypeId
matchToTypeId<int>() { return TypeId::INT; }

template <>
constexpr TypeId
matchToTypeId<std::string>() { return TypeId::STRING; }


		}
	}
}

#endif