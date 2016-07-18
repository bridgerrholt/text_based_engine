/// @file database_handle.h
/// Definition of the class tbe::sql::DatabaseHandle.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_DATABASE_HANDLE_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_DATABASE_HANDLE_H

#include <string>
#include <memory>

#include <sqlite3.h>

namespace tbe {
  namespace sql {

class DatabaseHandle
{
  public:
    DatabaseHandle();
    DatabaseHandle(sqlite3* database);
    DatabaseHandle(
      std::string const & fileName,
      int                 flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE
    );

    sqlite3 * const operator*() const;
    sqlite3 * const get()       const;

  private:
    /// Properly frees a query handle once out of scope.
    class HandleWrapper
    {
      public:
        /// Primary constructor.
        /// @param[in] handleSet Sets the @ref handle member.
        HandleWrapper(sqlite3* handleSet);

        /// Properly frees @ref handle.
        ~HandleWrapper();

        /// Immutable pointer to the query handle.
        sqlite3 * const handle;
    };

    /// Handles the open database or a nullptr to it.
    /// Does not ever change.
    std::shared_ptr<HandleWrapper> handle_;
};

  }
}

#endif