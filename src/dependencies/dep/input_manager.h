#ifndef _DEPENDENCIES_DEP_INPUT_MANAGER_H
#define _DEPENDENCIES_DEP_INPUT_MANAGER_H

#include <iostream>
#include <locale>

#include "format_string.h"

namespace dep {

class InputManager
{
public:
  InputManager(std::locale const & locale);

  FormatString get();
  FormatString get(std::string & inputString);

private:
  std::locale const & locale_;

};

  
}

#endif