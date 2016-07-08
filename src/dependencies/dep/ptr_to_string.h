/// @file ptr_to_string.h
/// Definition of the function template dep::ptrToString().

#ifndef _DEPENDENCIES_DEP_PTR_TO_STRING_H
#define _DEPENDENCIES_DEP_PTR_TO_STRING_H

#include <sstream>

namespace dep {
  
/// Reads an address to a string.
///
/// @tparam T The type of the value @p ptr points to.
/// @param[in] ptr The address to be read.
///
/// @return The address in string form.
template <class T>
std::string
ptrToString(T const * ptr)
{
  std::stringstream outStream;
  outStream << static_cast<void const *>(ptr);
  return outStream.str();
}



}

#endif
