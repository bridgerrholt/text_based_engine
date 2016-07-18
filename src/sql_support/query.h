/// @file query.h
/// Declaration of the tbe::sql::Query class.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_QUERY_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_QUERY_H

#include <vector>
#include <memory>
#include <string>

#include <sqlite3.h>

namespace tbe {
  namespace sql {
    
/// Manages a query handle (sqlite3_stmt) and provides methods for execution.
class Query
{
  public:
    /// Query text constructor.
    /// @param[in] database  The database handle to be used.
    /// @param[in] queryText The command(s) to be ran.
    Query(sqlite3* database, std::string const & queryText);

    Query(sqlite3    *   database,
          char const *   strStart,
          char const * & strTail);

    static
    std::vector<Query> createQueries(sqlite3           * database,
                                     std::string const & queryText);

    /// Advances the query to the next row.
    /// @return Whether there was a row or not.
    ///         In other words, returning true guarantees there is still a row to read from.
    bool nextRow();

    /// Throws an exception if the column count is undesired.
    /// @param[in] desiredCount The amount of columns required for no exception.
    void verifyColumnCount(int desiredCount);

    /// Outputs a text column as a string.
    /// 
    /// @param[in] columnIndex The index to read out.
    /// @return The column in string form.
    std::string readString(int columnIndex);

    // TODO: Make this function private,
    //       provide operations for reading out query data (such as readString).
    /// Returns the internal SQLite query.
    /// @return The managed sqlite3_stmt object's address.
    sqlite3_stmt* getHandle() const;


  private:
    /// Properly frees a query handle once out of scope.
    class HandleWrapper
    {
      public:
        /// Primary constructor.
        /// @param[in] handleSet Sets the @ref handle member.
        HandleWrapper(sqlite3_stmt* handleSet);

        /// Properly frees @ref handle.
        ~HandleWrapper();

        /// Immutable pointer to the query handle.
        sqlite3_stmt * const handle;
    };

    /// @param[out] containsSql Whether the text contained SQL or not.
    Query(sqlite3    *   database,
          char const *   strStart,
          char const * & strTail,
          bool         & containsSql);

    /// @return Whether the text contained SQL or not.
    bool coreConstruction(
          sqlite3    *   database,
          char const *   strStart,
          char const * & strTail);


    /// Creates a formatted display of the handle pointer.
    std::string getHandleString() const;


    /// The query handle.
    /// A shared_ptr is used because multiple references may be desired.
    std::shared_ptr<HandleWrapper> handle_;
};



  }
}

#endif