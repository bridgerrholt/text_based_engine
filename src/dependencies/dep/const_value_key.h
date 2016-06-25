/** @file const_value_key.h
    Declaration and definition of the dep::ConstValueKey class.

    @class dep::ConstValueKey
    Holds a constant value, can only be constructed by a passed class.
    The default type is size_t because it's primary purpose is holding an id or index.

    @param F The friend type, which is the only type able to create it.
    @param T The type of value to hold.
*/

#ifndef _DEPENDENCIES_DEP_CONST_VALUE_KEY_H
#define _DEPENDENCIES_DEP_CONST_VALUE_KEY_H

#include <iostream> // size_t

namespace dep {

template <class F, class T = size_t>
class ConstValueKey
{
  public:
    // Declares F as the only type able to construct it.
    friend F;

    /// The immutable value.
    const T value;

  private:
    /// Constructor only callable by @ref F.
    /// @param valueSet Sets @ref value, is not a const reference because
    /// T shouldn't be a very large type.
    ConstValueKey(T valueSet);
};



template <class F, class T>
ConstValueKey<F, T>::ConstValueKey(T valueSet) :
  value(valueSet)
{

}



}

#endif