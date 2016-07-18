#include "command_processor.h"

#include <stdexcept>

#include <dep/string_formatter.h>

namespace tbe {

CommandProcessor::CommandProcessor(std::locale const & localeSet) :
  locale(localeSet)
{
  commandMap_.insert({"quit",       QUIT});
  commandMap_.insert({"list-paths", LIST_PATHS});
}



CommandProcessor::Command
CommandProcessor::readCommand(std::string commandText)
{
  dep::StringFormatter strFor { locale, std::move(commandText) };

  if (strFor.trim().strRef().empty())
    return NO_COMMAND;

  std::string str = std::move(strFor).moveOut();

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
      return command;

    // Upcoming commands are all handled by the CommandProcessor.

    // Unknown enum code.
    default:
      throw std::runtime_error(
        "Invalid command code: " + std::to_string(command)
      );
  }
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

}