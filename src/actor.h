#ifndef TEXT_BASED_ENGINE_ACTOR_H
#define TEXT_BASED_ENGINE_ACTOR_H

#include <common/string_ref.h>

namespace tbe {

class Actor
{
  public:
    std::string name;
    int         nextId;
};


}

#endif