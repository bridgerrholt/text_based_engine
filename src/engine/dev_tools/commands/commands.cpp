/// @file commands.cpp
/// Declarations of the command classes.

#include "commands.h"

namespace tbe {
  namespace dev_tools {
    namespace commands {

template <>
CommandBase::Signature
Set::signature_ = {
  ArgumentBase::OPTION,
  ArgumentBase::OBJECT
};


template <>
RunInfo::State
Set::execute(ExecutionArgs data)
{
  auto var = data.stateMap.getVariable(dep::ofDynamic<arg_types::Option>(data.i->get())->data);
  ++data.i;

  if (var) {
    auto setTo = dep::ofDynamic<arg_types::Object>(data.i->get());
    if (var->get()->getTypeId() == setTo->data->getTypeId()) {
      var->reset(std::move(setTo->data.get()));
      return RunInfo::VALID;
    }
  }
  
  return RunInfo::INVALID;
}




template <>
CommandBase::Signature
ListPaths::signature_ = {

};


template <>
RunInfo::State
ListPaths::execute(ExecutionArgs data)
{
  return RunInfo::INVALID;
}


    }
  }
}