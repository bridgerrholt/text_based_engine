/// @file is_int.h
/// Declaration of the function dep::isInt().

#ifndef _DEPENDENCIES_DEP_IS_INT_H
#define _DEPENDENCIES_DEP_IS_INT_H

#include <string>

namespace dep {
  
/// Determines whether a given string represents an integer or not.
/// Does not strip the passed string of whitespace.
///
/// @param[in] str The given string.
/// @return Whether @p str represents an integer.
bool isInt(std::string const & str);

}

#endif