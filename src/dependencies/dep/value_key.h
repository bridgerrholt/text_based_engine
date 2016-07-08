/// @file value_key.h
/// Declaration and definition of the dep::ValueKey class.

/// @class dep::ValueKey
/// Template class that can only be constructed by the passed class.
/// Contains a variable that cannot be changed after construction.
///
/// @param F The friend type, which is the only type able to create it.
/// @param T The type of value to hold. By default is std::size_t because it's primary purpose is
///          to hold an id or an index.

#ifndef _DEPENDENCIES_DEP_VALUE_KEY_H
#define _DEPENDENCIES_DEP_VALUE_KEY_H

#include <stddef.h> // std::size_t

#include "basic_immutable_value.h"

namespace dep {

template <class F, class T = std::size_t>
class ValueKey
{
  public:
    // Declares F as the only type able to construct it.
    friend F;

    T get() const { return value_.get(); }


  private:
    /// The immutable value.
    /// Not const, but the underlying value is not able to change after construction.
    BasicImmutableValue<T> value_;

    /// Constructor only callable by @ref F.
    /// @param valueSet Sets @ref value, is not a const reference because
    ///                 T shouldn't be a very large type.
    ValueKey(T valueSet);
};



template <class F, class T>
ValueKey<F, T>::ValueKey(T valueSet) :
  value_(valueSet)
{

}



}

#endif