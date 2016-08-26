#include "command_processor.h"

namespace tbe {

CommandProcessor::CommandProcessor(
  std::locale const & localeSet,
  GameStateMap      & stateMapSet) :

  locale  (localeSet),
  stateMap(stateMapSet)
{
  commandMap_.insert({ "quit",       commands::QUIT });
  commandMap_.insert({ "list-paths", commands::LIST_PATHS });
  commandMap_.insert({ "dev-on",     commands::DEV_ON });

  commandObjects_.emplace(
    "set", std::unique_ptr<CommandBase> (new commands::Set {}));
}



commands::Kind
CommandProcessor::readCommand(std::string commandText)
{
  dep::StringFormatter strFor { locale, std::move(commandText) };

  if (strFor.trim().strRef().empty())
    return commands::NO_COMMAND;

  std::string str = strFor.moveOut();

  if (str.substr(0, commandLeader_.size()) != commandLeader_)
    return commands::NO_COMMAND;

  str.erase(0, commandLeader_.size());

  if (commandMap_.count(str) == 0)
    throw std::runtime_error("No command: " + str);

  commands::Kind command = commandMap_[str];

  switch (command) {
    // Upcoming commands are all handled by the Engine.
    case commands::NO_COMMAND:
    case commands::QUIT:
    case commands::LIST_PATHS:
    case commands::DEV_ON:
      return command;

    // Upcoming commands are all handled by the CommandProcessor.

    // Unknown enum code.
    default:
      throw std::runtime_error(
        "Invalid command code: " + std::to_string(command)
      );
  }
}



RunInfo::State
CommandProcessor::readCommand(std::string     commandText,
                                      commands::Kind& command)
{
  dep::StringFormatter strFor { locale, std::move(commandText) };

  if (strFor.trim().strRef().empty()) {
    command = commands::NO_COMMAND;
    return RunInfo::NONE;
  }

  std::string str = strFor.moveOut();

  if (str.substr(0, commandLeader_.size()) != commandLeader_) {
    command = commands::NO_COMMAND;
    return RunInfo::NONE;
  }

  str.erase(0, commandLeader_.size());

  if (commandMap_.count(str) == 0) {
    command = commands::NO_COMMAND;
    return RunInfo::INVALID;
  }

  command = commandMap_[str];

  switch (command) {
    // Upcoming commands are all handled by the Engine.
    case commands::NO_COMMAND:
    case commands::QUIT:
    case commands::LIST_PATHS:
    case commands::DEV_ON:
      return RunInfo::VALID;

    // Upcoming commands are all handled by the CommandProcessor.

    // Unknown enum code.
    default:
      return RunInfo::INVALID;
  }
}



RunInfo
CommandProcessor::readCommandV2(std::string commandText)
{
  // No command if the command leader was not at the beginning.
  if (commandText.substr(0, commandLeader_.size()) != commandLeader_) {
    return { RunInfo::NONE };
  }

  // Starts past the leader.
  auto i = commandText.begin() + commandLeader_.size();

  std::string commandName;

  while (i != commandText.end()) {
    if (std::isspace(*i, locale)) {
      if (commandName.empty())
        continue;
      else
        break;
    }

    commandName += *i;

    ++i;
  }

  if (commandName.empty() || commandObjects_.count(commandName) == 0)
    return { RunInfo::NONE };

  if (i != commandText.end())
    ++i;

  commandText.erase(commandText.begin(), i);

  return commandObjects_[commandName]->run(
    stateMap, commandText, locale
  );
}



void
CommandProcessor::setCommandLeader(std::string commandLeader)
{
  dep::StringFormatter str { locale, std::move(commandLeader) };

  if (str.trim().strRef().empty()) {
    throw std::runtime_error(
      "Command leader must have non-whitespace contents"
    );
  }

  commandLeader_ = std::move(str).moveOut();
}



void
CommandProcessor::pushCommandState(
  typename CommandStateMap::key_type key,
           CommandState              commandState)
{
  commandStates_.insert({std::move(key), std::move(commandState)});
}



void
CommandProcessor::setCurrentCommandState(
      typename CommandStateMap::key_type currentCommandState)
{
  assert(commandStates_.count(currentCommandState) != 0);

  currentCommandState_ = std::move(currentCommandState);
}



}