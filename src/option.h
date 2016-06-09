#ifndef TEXT_BASED_ENGINE_OPTION_H
#define TEXT_BASED_ENGINE_OPTION_H

#include <common/string_ref.h>

namespace tbe {

class Option
{
  public:
    int         characterId;
    int         optionListId;
    std::string textDisplay;
    std::string textSpeak;
    int         nextId;
};

}

#endif