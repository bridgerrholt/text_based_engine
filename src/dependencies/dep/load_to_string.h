#ifndef _DEPENDENCIES_DEP_LOAD_TO_STRING_H
#define _DEPENDENCIES_DEP_LOAD_TO_STRING_H

#include <common/string_ref.h>

namespace dep {

std::string loadToString(com::StringRef fileName);

void        loadToString(com::StringRef fileName, 
  std::string& returnString);

}

#endif
