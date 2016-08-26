/// @file parameter_list.h
/// Declarations of the class tbe::ParameterList.

#ifndef TEXT_BASED_ENGINE_ENGINE_PARAMETER_LIST_H
#define TEXT_BASED_ENGINE_ENGINE_PARAMETER_LIST_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "../argument.h"

namespace tbe {

class ParameterInfoBase
{
  public:
    ArgumentBase::Kind const kind;
};


typedef std::unique_ptr<ParameterInfoBase> DynamicParameterInfo;




class ParameterList
{
  public:
    std::vector<DynamicParameterInfo> paramters;
};

}

#endif