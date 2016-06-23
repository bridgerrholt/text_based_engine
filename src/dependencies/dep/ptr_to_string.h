/** @file ptr_to_string.h
    Declaration and definition of the dep::ptrToString function.


    @fn dep::ptrToString
    Reads an address to a string.

    @param[in] ptr The address to be read.
    @return The address in string form.
*/

#ifndef _DEPENDENCIES_DEP_PTR_TO_STRING_H
#define _DEPENDENCIES_DEP_PTR_TO_STRING_H

#include <sstream>

namespace dep {

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
