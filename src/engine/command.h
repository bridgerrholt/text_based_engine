/// @file command.h
/// Declarations of the abstract class tbe::CommandBase.

#ifndef TEXT_BASED_ENGINE_ENGINE_COMMAND_H
#define TEXT_BASED_ENGINE_ENGINE_COMMAND_H

#include <string>
#include <vector>
#include <unordered_map>
#include <locale>

#include "../sql_support/types/kind.h"

#include "parameter_list.h"
//#include "basic_command_processor.h"
#include "game_state_map.h"
#include "argument.h"

namespace tbe {

class CommandBase
{
  public:
    typedef std::vector<DynamicArgument>    ArgumentList;
    typedef std::vector<ArgumentBase::Kind> Signature;

    class RunData
    {
      public:
        InputInfo         input;
        commands::Command command;
        ArgumentList      args;
    };

    CommandBase();

    virtual
    ~CommandBase() = 0;
    
    RunData run(GameStateMap      & stateMap,
                std::string const & args,
                std::locale const & locale);

  private:
    virtual
    commands::Command getKindId() const = 0;

    virtual
    InputInfo execute(GameStateMap &                     stateMap,
                      ArgumentList::const_iterator       i,
                      ArgumentList::const_iterator const end) = 0;

    virtual
    Signature const & getSignature() const = 0;

};

}

#endif