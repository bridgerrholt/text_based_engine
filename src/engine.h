#ifndef TEXT_BASED_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_H

#include <unordered_map>

#include <common/string_ref.h>

namespace tbe {

class Engine
{
  public:
    Engine();

    void loadConfig(com::StringRef fileName);

  private:
    void resetPaths();

    typedef std::unordered_map<std::string, std::string> PathMap;
    PathMap paths_;

};

}

#endif