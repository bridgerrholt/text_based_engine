/// @file check_file_exists.cpp
/// Definition of the overloaded function @ref dep::checkFileExists().

#include "check_file_exists.h"

#include <sys/stat.h>

namespace dep {

bool
checkFileExists(std::string const & fileName)
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