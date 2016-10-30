/// @file var_list.h
/// Declares the typedefs tbe::sql::DynamicVar and tbe::sql::VarList.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_VAR_LIST_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_VAR_LIST_H

#include <vector>
#include <memory>

#include "../object_ptr.h"

namespace tbe {
  namespace dev_tools {
    namespace types {

typedef std::vector<ObjectPtr> ObjectList;

    }
  }
}

#endif