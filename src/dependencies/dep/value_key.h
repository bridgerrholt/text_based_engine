/// @file value_key.h
/// Declaration and definition of the class template dep::ValueKey.

/// @class dep::ValueKey
/// Class template that can only be constructed by a passed class.
/// Contains a variable that cannot be changed after construction.
///
/// @param F The friend type, which is the only type able to create it.
/// @param T The type of value to hold. By default is std::size_t because it's primary purpose is
///          to hold an id or an index.

#ifndef _DEPENDENCIES_DEP_VALUE_KEY_H
#define _DEPENDENCIES_DEP_VALUE_KEY_H

#include <stddef.h> // std::size_t
#include <utility> // std::move

#include "basic_immutable_value.h"

namespace dep {

template <class F, class T = std::size_t>
class ValueKey
{
  public:
    /// Declares F as the only type able to construct it.
    friend F;

    /// Returns the underlying value.
    T         get()    const { return value_.get(); }

    /// Returns a const reference to the underlying value.
    T const & getRef() const { return value_.getRef(); }


  private:
    /// Constructor only callable by @ref F.
    /// @param valueSet Sets @ref value. Move semantics may be used.
    ValueKey(T valueSet);

    /// The immutable value.
    /// Not const, but this variable's underlying value is not able to change after construction.
    BasicImmutableValue<T> value_;
};



template <class F, class T>
ValueKey<F, T>::ValueKey(T valueSet) :
  value_(std::move(valueSet))
{

}

}

#endif