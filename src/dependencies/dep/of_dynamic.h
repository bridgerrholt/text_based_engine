/// @file of_dynamic.h
/// Definition of the overloaded function template @ref dep::ofDynamic().

#ifndef _DEPENDENCIES_DEP_OF_DYNAMIC_H
#define _DEPENDENCIES_DEP_OF_DYNAMIC_H

#include <stdexcept>
#include <string>

namespace dep {
  namespace internal {
  
std::string const exceptionMessage =
  "Invalid dynamic_cast within function ofDynamic<T, F>(F& from)";

  }
  
/// Dynamically casts a given pointer to a pointer to a given type.
/// Casts a pointer to an object of F to a pointer to an object of T. Throws an error
/// if the cast failed.
///
/// @tparam T The type to cast @p from to.
/// @tparam F The type (of @p from) to cast from.
/// @param[in] from Pointer to the F object.
///
/// @return The dynamically-casted pointer to a T object.
template <class T, class F>
T*
ofDynamic(F* from)
{
  T* returnPtr = dynamic_cast<T*>(from);

  if (returnPtr)
    return returnPtr;

  else {
    throw std::runtime_error(exceptionMessage);
  }
}


template <class T, class F>
T*
ofDynamic(F& from)
{
  return ofDynamic<T>(&from);
}



/// Const version of ofDynamic().
template <class T, class F>
T const *
ofDynamic(F const * from)
{
  T const * returnPtr = dynamic_cast<T const *>(from);

  if (returnPtr)
    return returnPtr;

  else {
    throw std::runtime_error(exceptionMessage);
  }
}


template <class T, class F>
T const *
ofDynamic(F const & from)
{
  return ofDynamic<T>(&from);
}

}

#endif