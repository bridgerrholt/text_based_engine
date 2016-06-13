/** @file engine.h
    Declaration of the Engine class.

    @class tbe::Engine
    Provides the main functionality, loads a database and runs the game.
*/

#ifndef TEXT_BASED_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_H

#include <vector>
#include <map>
#include <memory>

#include <common/string_ref.h>

#include <sqlite3.h>

#include "sql_helpers/query.h"

#include "sql_helpers/objects/include.h"

namespace tbe {

class Engine
{
  public:
    /// Primary constructor.
    /// Doesn't load anything, just sets member variables.
    Engine();

    /// Unloads the database (if opened) and all active queries.
    ~Engine();

    /// Opens the provided database and gathers needed data.
    /// If a database is already open, it is closed before the new one is opened.
    /// @param[in] fileName The path and name of the database file.
    void loadDatabase(com::StringRef fileName);

    /// Runs the actual game.
    void run();


  private:
    /** Opens the given database file.
        Ensures the given file exists and attempts to open it.
        If anything fails, an exception is thrown.
        @param[in] fileName The path and name of the database file.
    */
    void openDatabase(com::StringRef fileName);

    /// Attempts to close the database.
    void closeDatabase();


    bool databaseOpened_;
    sqlite3* database_;

    std::vector<sql::Actor::Data> actors_;

    size_t waitTime_;

};

}

#endif