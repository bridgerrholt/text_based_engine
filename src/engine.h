#ifndef TEXT_BASED_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_H

#include <unordered_map>

#include <common/string_ref.h>

#include <sqlite3.h>

namespace tbe {

class Engine
{
  public:
    Engine();
    ~Engine();

    void loadDatabase(com::StringRef fileName);

  private:
    bool databaseLoaded_;
    sqlite3* database_;


};

}

#endif