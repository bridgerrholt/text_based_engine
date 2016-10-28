/// @file dynamic_type.h
/// Declaration of the class tbe::sql::DynamicVariable.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_DYNAMIC_VARIABLE_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_DYNAMIC_VARIABLE_H

#include <memory>

#include "types/basic_type.h"


namespace tbe {
  namespace sql {

using DynamicTypePtr = std::unique_ptr<DynamicType>;

class DynamicVariable : public DynamicTypePtr
{
  public:
    constexpr DynamicVariable() {}
    DynamicVariable(DynamicTypePtr ptr);

    template <class T>
    DynamicVariable(T data) :
      DynamicTypePtr(new types::BasicType<T>(data)) {}
};


  }
}

#endif