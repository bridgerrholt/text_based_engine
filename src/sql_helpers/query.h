/** @file query.h
    Declaration of the tbe::sql::Query class.

    @class tbe::sql::Query
    Manages a query handle (sqlite3_stmt) and provides methods for execution.
*/

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_H

#include <vector>
#include <memory>
#include <string>

#include <sqlite3.h>

#include "query_data.h"

namespace tbe {
  namespace sql {

class Query
{
  public:
    /// Query text constructor.
    /// @param[in] database  The database handle to be used.
    /// @param[in] queryText The command(s) to be ran.
    Query(sqlite3* database, std::string const & queryText);

    /// QueryDataFull constructor.
    /// @param[in] queryData All the information about the query.
    /// @param[in] tableName The table that the query will be executed on.
    Query(QueryDataFull const & queryData,
          std::string   const & tableName);

    /// Advances the query to the next row.
    /// @return Whether there was a next row or not.
    bool nextRow();

    /// Throws an exception if the column count is undesired.
    /// @param[in] desiredCount The amount of columns required for no exception.
    void verifyColumnCount(int desiredCount);

    /** Outputs a text column as a string.
        
        @param[in] columnIndex The index to read out.
        @return The column in string form.
    */
    std::string readString(int columnIndex);

    /// Returns the managed sqlite3_stmt object's address.
    /// @return The managed handle.
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

        /// @return @ref handle.
        sqlite3_stmt& operator* ();
        /// @return @ref handle.
        sqlite3_stmt* operator->();

        /// Immutable pointer to the query handle.
        sqlite3_stmt * const handle;
    };


    /// Creates a formatted display of the handle pointer.
    std::string getHandleString() const;


    /// The query handle.
    /// A shared_ptr is used because multiple references may be desired.
    std::shared_ptr<HandleWrapper> handle_;
};

  }
}

#endif