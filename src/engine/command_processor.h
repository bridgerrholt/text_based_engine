#ifndef TEXT_BASED_ENGINE_ENGINE_COMMAND_PROCESSOR_H
#define TEXT_BASED_ENGINE_ENGINE_COMMAND_PROCESSOR_H

#include <locale>
#include <string>
#include <unordered_map>

namespace tbe {

class CommandProcessor
{
  public:
    enum Command
    {
      NO_COMMAND = 0,

      QUIT,
      LIST_PATHS
    };


    CommandProcessor(std::locale const & localeSet);

    /// Attempts to read the given line.
    /// @return The command.
    Command readCommand(std::string commandText);

    void setCommandLeader(std::string commandLeader);

    std::locale const & locale;

  private:
    /// Must be at the front of a command.
    std::string commandLeader_ = ":";

    /// Maps each command name to a unique index.
    std::unordered_map<std::string, Command> commandMap_;
};

}

#endif