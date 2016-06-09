#ifndef TEXT_BASED_ENGINE_RESPONSE_H
#define TEXT_BASED_ENGINE_RESPONSE_H

#include <string>

namespace tbe {

class Response
{
  public:
    std::string text;
    int         next;
};

}

#endif