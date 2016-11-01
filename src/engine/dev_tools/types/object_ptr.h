/// @file object_ptr.h
/// Declaration of the smart pointer tbe::dev_tools::types::ObjectPtr.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_OBJECT_PTR_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_OBJECT_PTR_H

#include <memory> // std::unique_ptr

#include "common/basic_object.h"

namespace tbe {
  namespace dev_tools {
    namespace types {

using ObjectPtr = std::unique_ptr<ObjectBase>;


template <class T>
ObjectPtr makeObjectPtr(T data)
{
  return ObjectPtr { new types::BasicObject<T>(std::move(data)) };
}


    }
  }
}

#endif