#include "engine.h"

#include <rapidjson/document.h>

#include <dep/load_to_string.h>

namespace tbe {

Engine::Engine()
{

}



void
Engine::loadConfig(com::StringRef fileName)
{
  using namespace rapidjson;

  Document document;
  document.Parse(dep::loadToString(fileName).c_str());

  assert(document.IsObject());

  if (document.HasMember("paths")) {

  }
}



void
Engine::resetPaths()
{

}



}
