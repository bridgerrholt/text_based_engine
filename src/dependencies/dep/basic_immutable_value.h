/** @file basic_immutable_value.h
    Declaration and definition of the dep::BasicImmutableValue class.

    @class dep::BasicImmutableValue
    Holds a value (of any type) that can only be set at construction.

    @param T The type of value to hold.
*/

#ifndef _DEPENDENCIES_DEP_BASIC_IMMUTABLE_VALUE_H
#define _DEPENDENCIES_DEP_BASIC_IMMUTABLE_VALUE_H

namespace dep {

template <class T>
class BasicImmutableValue
{
  public:
    BasicImmutableValue(T value);

    T get() const { return value_; }

  private:
    T value_;
};



template <class T>
BasicImmutableValue<T>::BasicImmutableValue(T value) :
  value_(value)
{

}

}

#endif