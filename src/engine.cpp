#include "engine.h"

#include <stdexcept>

#include <dep/check_file_exists.h>

namespace tbe {

Engine::Engine()
{

}



Engine::~Engine()
{
  if (databaseLoaded_)
    sqlite3_close(database_);
}



void
Engine::loadDatabase(com::StringRef fileName)
{
  if (databaseLoaded_)
    sqlite3_close(database_);

  int resultCode = sqlite3_open(fileName.c_str(), &database_);

  if (resultCode != SQLITE_OK) {
    sqlite3_close(database_);
    throw std::runtime_error("Can't open database: " + fileName);
  }

  databaseLoaded_ = true;
}



}
