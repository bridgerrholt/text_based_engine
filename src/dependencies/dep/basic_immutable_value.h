/// @file basic_immutable_value.h
/// Declaration and definition of the dep::BasicImmutableValue class.

/// @class dep::BasicImmutableValue
/// Holds a value (of any type) that can only be set at construction.
///
/// @param T The type of value to hold.

#ifndef _DEPENDENCIES_DEP_BASIC_IMMUTABLE_VALUE_H
#define _DEPENDENCIES_DEP_BASIC_IMMUTABLE_VALUE_H

namespace dep {

template <class T>
class BasicImmutableValue
{
  public:
    /// Primary constructor.
    /// @param value Sets the underlying @ref value_ member.
    BasicImmutableValue(T value);

    /// Returns the member @ref value_.
    T get() const { return value_; }

  private:
    /// The immutable value.
    /// Not const because of issues around the assignment operator.
    T value_;
};



template <class T>
BasicImmutableValue<T>::BasicImmutableValue(T value) :
  value_(value)
{

}

}

#endif