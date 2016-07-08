/// @file var_list.h
/// Declares the typedefs tbe::sql::DynamicVar and tbe::sql::VarList.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_COMMON_VAR_LIST_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_COMMON_VAR_LIST_H

#include <vector>
#include <memory>

#include "../dynamic_type.h"

namespace tbe {
  namespace sql {

typedef std::unique_ptr<DynamicType> DynamicVar;
typedef std::vector    <DynamicVar>  VarList;

  }
}

#endif