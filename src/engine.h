/** @file engine.h
    Declaration of the tbe::Engine class.

    @class tbe::Engine
    Provides the main functionality, loads a database and runs the dialogue.
*/

#ifndef TEXT_BASED_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_H

#include <vector>
#include <locale>
#include <string>

#include <sqlite3.h>

#include <dep/input_manager.h>
#include <dep/sleep_event.h>

#include "sql_helpers/objects/include.h"
#include "sql_helpers/mapped_query.h"
#include "sql_helpers/column_list.h"

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
    void loadDatabase(std::string const & fileName);

    /// Runs the actual game.
    void run();


  private:
    /** Opens the given database file.
        Ensures the given file exists and attempts to open it.
        If anything fails, an exception is thrown.
        
        @param[in] fileName The path and name of the database file.
    */
    void openDatabase(std::string const & fileName);

    /// Attempts to close the database.
    void closeDatabase();


    /// The program-wide locale.
    std::locale locale_;

    /// Primary InputManager.
    dep::InputManager inputManager_;

    /// Is true while a database is successfully opened.
    bool databaseOpened_;

    /// Handles the currently open database.
    sqlite3* database_;

    /// All the actors specified in the database.
    sql::MappedQuery::QueryResult actors_;

    /// The primary SleepEvent.
    /// Secondary SleepEvents may be added in the future.
    dep::SleepEventDefault sleepEvent_;


    sql::ColumnList optionColumns_;
};

}

#endif