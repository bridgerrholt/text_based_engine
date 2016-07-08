/// @file load_to_string.h
/// Declaration of the overloaded function dep::loadToString().

#ifndef _DEPENDENCIES_DEP_LOAD_TO_STRING_H
#define _DEPENDENCIES_DEP_LOAD_TO_STRING_H

#include <string>

namespace dep {
  
/// Reads the given file to a string.
///
/// @param[in] fileName The full path and name of the target file.
/// @return The constructed string with the file's contents.
std::string loadToString(std::string const & fileName);

/// @param[out] returnString The user-created string that the file gets read to.
void        loadToString(std::string const & fileName, 
                         std::string       & returnString);

}

#endif
