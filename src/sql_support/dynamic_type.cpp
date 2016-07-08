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



types::Kind
DynamicType::getKind() const
{
  return kind_;
}



  }
}