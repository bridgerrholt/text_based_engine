#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_VAR_LIST_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_VAR_LIST_H

#include <vector>

#include "dynamic_type.h"

namespace tbe {
  namespace sql {

typedef std::unique_ptr<DynamicType> DynamicVar;
typedef std::vector    <DynamicVar>  VarList;

  }
}

#endif