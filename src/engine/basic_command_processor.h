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

namespace tbe {
  namespace commands {

enum Command
{
  NO_COMMAND = 0,

  QUIT,
  LIST_PATHS,
  DEV_ON,

  SET
};

  }
  
enum InputInfo
{
  NONE = 0,
  INVALID,
  VALID
};


template <class T>
class BasicCommandProcessor
{
  public:
    
    typedef std::vector<commands::Command>      CommandState;
    typedef std::unordered_map<T, CommandState> CommandStateMap;


    BasicCommandProcessor(std::locale  const & localeSet,
                          GameStateMap       & stateMapSet);

    /// Attempts to read the given line.
    /// @return The command.
    commands::Command readCommand(std::string commandText);

    /// @return Info about what the user inputted.
    InputInfo readCommand(std::string        commandText,
                          commands::Command& command);

    CommandBase::RunData readCommandV2(std::string commandText);

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
    std::string commandLeader_ = ":";

    /// Maps each command name to a unique index.
    std::unordered_map<std::string, commands::Command> commandMap_;

    /// Expresses available commands, each CommandState is a list of available commands.
    /// Will never decrease in size, can be increased with pushCommandState().
    /// If no command states are specified, all commands are valid.
    CommandStateMap commandStates_;

    /// Index of @ref commandStates_ to be used as the current command state.
    /// Can be set with setCurrentCommandState.
    typename
    CommandStateMap::key_type currentCommandState_;

    typedef std::function<InputInfo(
      std::vector<std::string>, GameStateMap&
    )> CommandFunction;

    std::unordered_map<std::string, CommandFunction> commandFunctions_;

    std::unordered_map<std::string,
                       std::unique_ptr<CommandBase> > commandObjects_;
};




template <class T>
BasicCommandProcessor<T>::BasicCommandProcessor(
  std::locale const & localeSet,
  GameStateMap      & stateMapSet) :

  locale  (localeSet),
  stateMap(stateMapSet)
{
  commandMap_.insert({"quit",       commands::QUIT});
  commandMap_.insert({"list-paths", commands::LIST_PATHS});
  commandMap_.insert({"dev-on",     commands::DEV_ON});
}



template <class T>
commands::Command
BasicCommandProcessor<T>::readCommand(std::string commandText)
{
  dep::StringFormatter strFor { locale, std::move(commandText) };

  if (strFor.trim().strRef().empty())
    return NO_COMMAND;

  std::string str = strFor.moveOut();

  if (str.substr(0, commandLeader_.size()) != commandLeader_)
    return NO_COMMAND;

  str.erase(0, commandLeader_.size());

  if (commandMap_.count(str) == 0)
    throw std::runtime_error("No command: " + str);

  Command command = commandMap_[str];

  switch (command) {
    // Upcoming commands are all handled by the Engine.
    case NO_COMMAND:
    case QUIT:
    case LIST_PATHS:
    case DEV_ON:
      return command;

    // Upcoming commands are all handled by the CommandProcessor.

    // Unknown enum code.
    default:
      throw std::runtime_error(
        "Invalid command code: " + std::to_string(command)
      );
  }
}



template <class T>
InputInfo
BasicCommandProcessor<T>::readCommand(std::string        commandText,
                                      commands::Command& command)
{
  dep::StringFormatter strFor { locale, std::move(commandText) };

  if (strFor.trim().strRef().empty()) {
    command = commands::NO_COMMAND;
    return NONE;
  }

  std::string str = strFor.moveOut();

  if (str.substr(0, commandLeader_.size()) != commandLeader_) {
    command = commands::NO_COMMAND;
    return NONE;
  }

  str.erase(0, commandLeader_.size());

  if (commandMap_.count(str) == 0) {
    command = commands::NO_COMMAND;
    return INVALID;
  }

  command = commandMap_[str];

  switch (command) {
    // Upcoming commands are all handled by the Engine.
    case commands::NO_COMMAND:
    case commands::QUIT:
    case commands::LIST_PATHS:
    case commands::DEV_ON:
      return VALID;

    // Upcoming commands are all handled by the CommandProcessor.

    // Unknown enum code.
    default:
      return INVALID;
  }
}



template <class T>
CommandBase::RunData
BasicCommandProcessor<T>::readCommandV2(std::string commandText)
{
  if (commandText.substr(0, commandLeader_.size()) != commandLeader_) {
    return NONE
  }

  auto i = commandText.begin() + commandLeader_.size();

  std::vector<std::string> commands { 1 };

  while (i != commandText.end()) {
    auto & command = commands.back();

    if (std::isspace(*i, locale)) {
      if (!command.empty())
        commands.emplace_back();
    }
    else {
      command += *i;
    }

    ++i;
  }

  if (commandFunctions_.count(commands[0]) == 0)
    return NONE;

  commands.erase(commands.begin());
  return commandFunctions_[commands[0]](commands, stateMap);
}



template <class T>
void
BasicCommandProcessor<T>::setCommandLeader(std::string commandLeader)
{
  dep::StringFormatter str { locale, std::move(commandLeader) };

  if (str.trim().strRef().empty()) {
    throw std::runtime_error(
      "Command leader must have non-whitespace contents"
    );
  }

  commandLeader_ = std::move(str).moveOut();
}



template <class T>
void
BasicCommandProcessor<T>::pushCommandState(
  typename CommandStateMap::key_type key,
           CommandState              commandState)
{
  commandStates_.insert({std::move(key), std::move(commandState)});
}



template <class T>
void
BasicCommandProcessor<T>::setCurrentCommandState(
      typename CommandStateMap::key_type currentCommandState)
{
  assert(commandStates_.count(currentCommandState) != 0);

  currentCommandState_ = std::move(currentCommandState);
}




}

#endif