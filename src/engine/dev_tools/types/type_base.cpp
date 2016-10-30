/// @file dynamic_type.cpp
/// Definition of the abstract base class tbe::sql::DynamicType.

#include "type_base.h"

namespace tbe {
  namespace dev_tools {
    namespace types {

TypeBase::TypeBase(types::Kind kind) :
  kind_(kind)
{

}



TypeBase::~TypeBase()
{

}


    }
  }
}