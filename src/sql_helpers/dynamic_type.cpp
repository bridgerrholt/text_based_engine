#include "dynamic_type.h"

namespace tbe {
  namespace sql {

DynamicType::DynamicType(Kind kind) :
  kind_(kind)
{

}



DynamicType::~DynamicType()
{

}



DynamicType::Kind
DynamicType::getKind() const
{
  return kind_;
}



  }
}