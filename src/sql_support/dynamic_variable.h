/// @file dynamic_type.h
/// Declaration of the class tbe::sql::DynamicVariable.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_DYNAMIC_VARIABLE_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_DYNAMIC_VARIABLE_H

#include <memory>

#include "types/basic_type.h"


namespace tbe {
  namespace sql {

class DynamicVariable
{
  public:
    typedef std::unique_ptr<DynamicType> ObjectType;

    DynamicVariable();
    DynamicVariable(ObjectType object);

    template <class T>
    DynamicVariable(T data) : object_(new BasicType(data))
    { }

  private:
    ObjectType object_;
};


  }
}

#endif