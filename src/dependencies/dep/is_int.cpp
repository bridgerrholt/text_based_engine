/// @file is_int.cpp
/// Definition of the function dep::isInt().

#include "is_int.h"

#include <cstdlib>

namespace dep {

bool isInt(std::string const & str)
{
  if (str.empty() ||
      ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+')))
        return false;

  char* p;
  strtol(str.c_str(), &p, 10);

  return (*p == 0);
}

}