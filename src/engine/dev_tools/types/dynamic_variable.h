/// @file dynamic_type.h
/// Declaration of the class tbe::sql::DynamicVariable.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_DYNAMIC_VARIABLE_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_DYNAMIC_VARIABLE_H

#include <memory>

#include <dep/basic_dynamic_ptr.h>

#include "common/basic_type.h"


namespace tbe {
  namespace dev_tools {
    namespace types {

using DynamicTypePtr  = std::unique_ptr<TypeBase>;
//using DynamicVariable = dep::BasicDynamicPtr<DynamicTypePtr, types::BasicType>;


template <typename T>
DynamicTypePtr makeDynamicVariable(T data)
{
  //return dep::makeDynamicPtr<DynamicTypePtr, types::BasicType, T>(data);
  return DynamicTypePtr { new types::BasicType<T>(std::move(data)) };
}


    }
  }
}

#endif