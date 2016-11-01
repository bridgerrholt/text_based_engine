/// @file object_list.h
/// Defines the alias tbe::dev_tools::types::ObjectList.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_OBJECT_LIST_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_OBJECT_LIST_H

#include <vector>
#include <memory>

#include "../object_ptr.h"

namespace tbe {
  namespace dev_tools {
    namespace types {

using ObjectList = std::vector<ObjectPtr>;

    }
  }
}

#endif