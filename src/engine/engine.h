/// @file engine.h
/// Declaration of the class tbe::Engine.

#ifndef TEXT_BASED_ENGINE_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_ENGINE_H

#include <locale>
#include <string>
#include <unordered_map>

#include <sqlite3.h>

#include <dep/input_manager.h>
#include <dep/sleep_event.h>

#include "../sql_support/common/query_result.h"

#include "../sql_support/column_list.h"
#include "../sql_support/database_handle.h"

#include "command_processor.h"
#include "ask_question.h"

namespace tbe {
  
/// Provides the program's primary functionality.
/// An Engine object is used to load a given database and run the database's described game.
class Engine
{
  public:
    /// Primary constructor.
    /// Doesn't actually load anything.
    Engine();

    /// Loads and runs the database if given, or asks for a location to create it.
    Engine(int argc, char* argv[]);

    /// Allows for a non-default locale.
    /// @param[in] locale The explicitally-specified locale.
    Engine(std::locale const & locale);

    /// Unloads the database (if opened) and all active queries.
    ~Engine();

    /// Opens the provided database and gathers needed data.
    /// If a database is already open, it is closed before the new one is opened.
    /// @param[in] fileName The path and name of the database file.
    void openDatabase(std::string const & fileName);
    
    /// Runs the actual game.
    void run();

    /// Calls loadDatabase() then run().
    /// @param[in] fileName The database file to be passed to loadDatabase().
    void run(std::string const & fileName);


    /// Runs the actual game.
    void runV2();

    /// Calls loadDatabase() then run().
    /// @param[in] fileName The database file to be passed to loadDatabase().
    void runV2(std::string const & fileName);

    /// Changes the locale.
    void setLocale(std::locale locale) { locale_ = std::move(locale); }


  private:
    class OptionDisplay
    {
      public:
        ResponseOptionList options;
        std::string        startText;
        std::string        endText;
    
    };

    class FullOptionList
    {
      public:
        ResponseOptionList optionList;
        std::size_t        startNum;
    };

    enum RunningState
    {
      /// Something is not right.
      BAD = 0,

      /// Lists all the characters.
      LOBBY,

      PLAYER_RESPONSE
    };


    /// Creates and opens a database, initializes the correct values.
    void createDatabase(std::string const & fileName);

    FullOptionList& currentOptions();

    /// Decides whether the program should return to the lobby based on a passed value
    /// representing the next dialogue id.
    /// If it should return to the lobby, it also marks @ref state_ as @ref LOBBY.
    ///
    /// @param[in] nextId If 0, the program should return to the lobby.
    /// @return Whether the program should return to the lobby or not.
    bool toLobby(int nextId);

    /// The program-wide locale.
    std::locale locale_;

    /// Primary InputManager.
    dep::InputManager inputManager_;

    sql::DatabaseHandle database_;

    /// All the actors specified in the database.
    sql::QueryResult actors_;

    /// Primary SleepEvent.
    /// Secondary SleepEvents may be added in the future.
    dep::SleepEvent sleepEvent_ = 500;

    /// Primary CommandProcessor.
    CommandProcessor commandProcessor_;

    RunningState state_ = BAD;

    bool inDevMode_ = false;

    std::unordered_map<RunningState, FullOptionList> stateOptions_;
};

}

#endif