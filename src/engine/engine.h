/// @file engine.h
/// Declaration of the class tbe::Engine.

#ifndef TEXT_BASED_ENGINE_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_ENGINE_H

#include <locale>
#include <string>

#include <sqlite3.h>

#include <dep/input_manager.h>
#include <dep/sleep_event.h>

#include "../sql_support/common/query_result.h"

#include "../sql_support/column_list.h"

#include "command_processor.h"

namespace tbe {
  
/// Provides the program's primary functionality.
/// An Engine object is used to load a given database and run the database's described game.
class Engine
{
  public:
    /// Primary constructor.
    /// Doesn't actually load anything.
    Engine();

    /// Allows for a non-default locale.
    /// @param[in] locale The explicitally-specified locale.
    Engine(std::locale const & locale);

    /// Unloads the database (if opened) and all active queries.
    ~Engine();

    /// Opens the provided database and gathers needed data.
    /// If a database is already open, it is closed before the new one is opened.
    /// @param[in] fileName The path and name of the database file.
    void loadDatabase(std::string const & fileName);
    
    /// Runs the actual game.
    void run();

    /// Calls loadDatabase() then run().
    /// @param[in] fileName The database file to be passed to loadDatabase().
    void run(std::string const & fileName);


  private:
    /// Opens the given database file.
    /// Ensures the given file exists and attempts to open it.
    /// If anything fails, an exception is thrown.
    ///
    /// @param[in] fileName The path and name of the database file.
    void openDatabase(std::string const & fileName);

    /// Attempts to close the database.
    void closeDatabase();


    /// The program-wide locale.
    std::locale locale_;

    /// Primary InputManager.
    dep::InputManager inputManager_;

    /// Is true while a database is successfully opened.
    bool databaseOpened_ = false;

    /// Handles the currently open database.
    sqlite3* database_ = 0;

    /// All the actors specified in the database.
    sql::QueryResult actors_;

    /// Primary SleepEvent.
    /// Secondary SleepEvents may be added in the future.
    dep::SleepEvent sleepEvent_ = 500;

    /// Primary CommandProcessor.
    CommandProcessor commandProcessor_;
};

}

#endif