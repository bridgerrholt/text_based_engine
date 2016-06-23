/// @file check_file_exists.cpp
/// Definitions of the dep::checkFileExists functions.

#include "check_file_exists.h"

#include <sys/stat.h>

namespace dep {

bool
checkFileExists(com::StringRef fileName)
{
  // Since stat uses C strings, .c_str() must be called regardless.
  return checkFileExists(fileName.c_str());
}



bool
checkFileExists(char const * fileName)
{
  struct stat buffer;
  return (stat(fileName, &buffer) == 0);
}



}