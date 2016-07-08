/// @file check_file_exists.h
/// Declaration of the dep::checkFileExists functions.

/// @fn dep::checkFileExists
/// Checks whether the provided file exists or not.
/// Should work on most platforms, but that's not at all gauranteed since sys/stat.h is used.
/// Accessibility is possibly checked instead existence.

/// @param fileName The full path and name of the target file.
/// @return Whether the file (@p fileName) exists or is accessible.

#ifndef _DEPENDENCIES_DEP_CHECK_FILE_EXISTS_H
#define _DEPENDENCIES_DEP_CHECK_FILE_EXISTS_H

#include <com/string_ref.h>

namespace dep {

bool checkFileExists(com::StringRef fileName);
bool checkFileExists(char const *   fileName);
  
}

#endif
