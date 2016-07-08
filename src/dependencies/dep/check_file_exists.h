/// @file check_file_exists.h
/// Declaration of the overloaded function dep::checkFileExists().

#ifndef _DEPENDENCIES_DEP_CHECK_FILE_EXISTS_H
#define _DEPENDENCIES_DEP_CHECK_FILE_EXISTS_H

#include <string>

namespace dep {
 
/// Checks whether the provided file exists or not.
/// Should work on most platforms, but that's not at all gauranteed since sys/stat.h is used.
/// Accessibility is possibly checked instead of existence.
///
/// @param fileName The full path and name of the target file.
/// @return Whether the file (@p fileName) exists or is accessible.
bool checkFileExists(std::string const & fileName);
bool checkFileExists(char        const * fileName);
  
}

#endif
