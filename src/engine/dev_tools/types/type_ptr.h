/// @file type_base.h
/// Declaration of the smart pointer tbe::dev_tools::types::TypePtr.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_PTR_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_PTR_H

#include <memory>

#include "type_base.h"

namespace tbe {
  namespace dev_tools {
    namespace types {

using TypePtr = std::unique_ptr<TypeBase>;

    }
  }
}

#endif