/// @file dynamic_type.cpp
/// Definition of the abstract base class tbe::sql::ObjectBase.

#include "object_base.h"

namespace tbe {
  namespace dev_tools {
    namespace types {

ObjectBase::ObjectBase(types::TypeId typeId) :
  typeId_(typeId)
{

}



ObjectBase::~ObjectBase()
{

}


    }
  }
}