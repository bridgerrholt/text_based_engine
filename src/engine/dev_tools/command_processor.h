#ifndef TEXT_BASED_ENGINE_ENGINE_COMMAND_PROCESSOR_H
#define TEXT_BASED_ENGINE_ENGINE_COMMAND_PROCESSOR_H

#include <locale>
#include <string>
#include <unordered_map>
#include <functional>

#include <stdexcept>
#include <cassert>

#include <dep/string_formatter.h>

#include "game_state_map.h"
#include "command.h"
#include "commands/kind.h"
#include "commands/commands.h"

#include "run_info.h"

namespace tbe {

// TODO: Get rid of template, make based on the enum within Engine,
//       but take that enum out into a separate file.
//       Or make it based on a string wrapper class.

class CommandProcessor
{
  public:
    
    typedef std::vector<commands::Kind>         CommandState;
    typedef std::unordered_map<std::size_t, CommandState> CommandStateMap;


    CommandProcessor(std::locale  const & localeSet,
                     GameStateMap       & stateMapSet);

    /// Attempts to read the given line.
    /// @return The command.
    commands::Kind readCommand(std::string commandText);

    /// @return Info about what the user inputted.
    RunInfo::State readCommand(std::string     commandText,
                               commands::Kind& command);

    RunInfo readCommandV2(std::string commandText);

    void setCommandLeader(std::string commandLeader);

    void pushCommandState(
      typename
      CommandStateMap::key_type key,
      CommandState commandState);

    void setCurrentCommandState(
      typename
      CommandStateMap::key_type currentCommandState);

    std::locale const & locale;
    GameStateMap      & stateMap;


  private:
    /// Must be at the front of a command.
    std::string commandLeader_ { ":" };

    /// Maps each command name to a command index.
    std::unordered_map<std::string, commands::Kind> commandMap_;

    /// Expresses available commands, each CommandState is a list of available commands.
    /// Will never decrease in size, can be increased with pushCommandState().
    /// If no command states are specified, all commands are valid.
    CommandStateMap commandStates_;

    /// Index of @ref commandStates_ to be used as the current command state.
    /// Can be set with setCurrentCommandState.
    typename
    CommandStateMap::key_type currentCommandState_;

    /*typedef std::function<InputInfo(
      std::vector<std::string>, GameStateMap&
    )> CommandFunction;

    std::unordered_map<std::string, CommandFunction> commandFunctions_;*/

    std::unordered_map<std::string,
                       std::unique_ptr<CommandBase> > commandObjects_;
};



}

#endif