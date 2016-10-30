/// @file type_base.h
/// Declaration of the smart pointer tbe::dev_tools::types::ObjectPtr.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_PTR_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_PTR_H

#include <memory>

#include "common/basic_object.h"

namespace tbe {
  namespace dev_tools {
    namespace types {

using ObjectPtr = std::unique_ptr<ObjectBase>;

template <typename T>
ObjectPtr makeObjectPtr(T data)
{
  return ObjectPtr { new types::BasicObject<T>(std::move(data)) };
}

    }
  }
}

#endif