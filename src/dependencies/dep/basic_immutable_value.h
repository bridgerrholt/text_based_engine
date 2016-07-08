/// @file basic_immutable_value.h
/// Declaration and definition of the class template dep::BasicImmutableValue.

#ifndef _DEPENDENCIES_DEP_BASIC_IMMUTABLE_VALUE_H
#define _DEPENDENCIES_DEP_BASIC_IMMUTABLE_VALUE_H

namespace dep {
  
/// Holds a value (of any type) that can only be set at construction.
/// The actual variable can be reassigned to a different instance, however.
///
/// @tparam T The type of value to hold.
template <class T>
class BasicImmutableValue
{
  public:
    /// Primary constructor.
    /// @param value Sets the underlying member (@ref value_).
    BasicImmutableValue(T value);

    /// Returns the underlying member (@ref value_).
    T         get()    const { return value_; }

    /// Returns a constant reference to the underlying member (@ref value_).
    /// This may be faster with some data types.
    T const & getRef() const { return value_; }


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