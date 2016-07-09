/// @file dynamic_type.cpp
/// Definition of the abstract base class tbe::sql::DynamicType.

#include "dynamic_type.h"

namespace tbe {
  namespace sql {

DynamicType::DynamicType(types::Kind kind) :
  kind_(kind)
{

}



DynamicType::~DynamicType()
{

}


  }
}