/// @file DatabaseHandle.cpp
/// Definition of the class tbe::sql::DatabaseHandle.

#include "database_handle.h"

#include <iostream>

namespace tbe {
  namespace sql {

DatabaseHandle::DatabaseHandle()
{

}


DatabaseHandle::DatabaseHandle(sqlite3* database) :
  handle_(new HandleWrapper(database))
{

}



DatabaseHandle::DatabaseHandle(std::string const & fileName,
                               int                 flags)
{
  sqlite3* database = nullptr;

  // Attempts to open the database.
  int resultCode = sqlite3_open_v2(
    fileName.c_str(), &database,
    flags, 0
  );

  if (resultCode != SQLITE_OK) {
    // Resources must be freed even on failure.
    sqlite3_close_v2(database);

    throw std::runtime_error(
      "Cannot open database:\n " +
        fileName + "\n"
      "because:\n" +
       sqlite3_errmsg(database)
    );
  }

  std::cerr << "Opened database (" << database << " : " << fileName << ")\n";

  handle_.reset(new HandleWrapper(database));
}


sqlite3 * const
DatabaseHandle::operator*() const
{
  return handle_->handle;
}



sqlite3* const
DatabaseHandle::get() const
{
  return handle_->handle;
}



// HandleWrapper

DatabaseHandle::HandleWrapper::HandleWrapper(sqlite3* handleSet) :
  handle(handleSet)
{

}



DatabaseHandle::HandleWrapper::~HandleWrapper()
{
  // Shouldn't be anything but SQLITE_OK.
  if (sqlite3_close_v2(handle) != SQLITE_OK)
    std::cerr << "Couldn't close database (" << handle << ")\n";

  else
    std::cerr << "Closed database (" << handle << ")\n";
}



  }
}