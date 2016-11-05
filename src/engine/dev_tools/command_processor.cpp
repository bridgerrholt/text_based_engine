#include "command_processor.h"

#include "commands/command_ptr.h"

#include "types/types.h"

#include <iostream>

namespace {
  
using namespace tbe;
using namespace tbe::dev_tools;


dev_tools::StateMap
makeStateMap(StateMap::VariableMap sharedVariables,
             StateMap::VariableMap globalVariables)
{
  using namespace commands;
	using namespace types;
	
  globalVariables.emplace("dev-mode", makeObjectPtr(false));
  globalVariables.emplace("to-quit",  makeObjectPtr(false));
  

  StateMap::CommandMap sharedCommands;
  sharedCommands.emplace("list-paths", makeCommandPtr<ListPaths>());
  
  StateMap::CommandMap globalCommands;
  globalCommands.emplace("set", makeCommandPtr<Set>());


  return {{std::move(sharedVariables), std::move(sharedCommands)},
          {std::move(globalVariables), std::move(globalCommands)}};
}

}


namespace tbe {
  namespace dev_tools {
  
CommandProcessor::CommandProcessor() :
	CommandProcessor({}, {})
{

}


CommandProcessor::CommandProcessor(
  StateMap::VariableMap sharedVariables,
  StateMap::VariableMap globalVariables) :

  stateMap_(::makeStateMap(
    std::move(sharedVariables), std::move(globalVariables)))
{

}



RunInfo
CommandProcessor::readCommand(std::string commandText)
{
  // No command if the command leader was not at the beginning.
  if (commandText.substr(0, commandLeader_.size()) != commandLeader_) {
    return { RunInfo::NONE };
  }

  // Starts past the leader.
  auto i = commandText.begin() + commandLeader_.size();

  std::string commandName;

  while (i != commandText.end()) {
    if (std::isspace(*i, std::locale())) {
      if (commandName.empty())
        continue;
      else
        break;
    }

    commandName += *i;

    ++i;
  }


  commands::CommandBase * command { nullptr };

  if (commandName.empty() || !(command = stateMap_.getCommand(commandName)))
    return { RunInfo::NONE };

  if (i != commandText.end())
    ++i;

  commandText.erase(commandText.begin(), i);

  auto toReturn = command->run(
    stateMap_, commandText, std::locale()
  );

	return toReturn;
}



void
CommandProcessor::setCommandLeader(std::string commandLeader)
{
  dep::StringFormatter str { std::move(commandLeader) };

  if (str.trim().strRef().empty()) {
    throw std::runtime_error(
      "Command leader must have non-whitespace contents"
    );
  }

  commandLeader_ = std::move(str).moveOut();
}


void
CommandProcessor::resetStateMap(StateMap::VariableMap sharedVariables,
																StateMap::VariableMap globalVariables)
{
	swap(stateMap_, makeStateMap(std::move(sharedVariables), std::move(globalVariables)));
}



  }
}