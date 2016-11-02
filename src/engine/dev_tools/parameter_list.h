/// @file parameter_list.h
/// Declarations of the class tbe::ParameterList.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_PARAMETER_LIST_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_PARAMETER_LIST_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "../argument.h"

namespace tbe {
	namespace dev_tools {


class ParameterInfoBase
{
	public:
		ArgumentBase::Kind const kind;
};


using ParameterInfoPtr = std::unique_ptr<ParameterInfoBase>;


class ParameterList
{
	public:
		std::vector<ParameterInfoPtr> parameters;
};


	}
}

#endif