#include "dynamic_variable.h"
#include "types/include.h"

namespace tbe {
  namespace sql {

DynamicVariable::DynamicVariable(DynamicTypePtr ptr) :
  DynamicTypePtr(std::move(ptr))
{

}


  }
}