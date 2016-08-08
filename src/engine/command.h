/// @file command.h
/// Declarations of the abstract class tbe::CommandBase.

#ifndef TEXT_BASED_ENGINE_ENGINE_COMMAND_H
#define TEXT_BASED_ENGINE_ENGINE_COMMAND_H

#include <string>
#include <vector>
#include <unordered_map>
#include <locale>

#include "../sql_support/types/kind.h"

#include "commands/kind.h"

#include "parameter_list.h"
//#include "basic_command_processor.h"
#include "game_state_map.h"
#include "argument.h"
#include "run_info.h"

namespace tbe {

class CommandBase
{
  public:
    typedef std::vector<ArgumentBase::Kind> Signature;

    CommandBase();

    virtual
    ~CommandBase() = 0;
    
    RunInfo run(GameStateMap      & stateMap,
                std::string const & args,
                std::locale const & locale);

  private:
    virtual
    commands::Kind getKind() const = 0;

    virtual
    RunInfo::State execute(GameStateMap &                     stateMap,
                           ArgumentList::const_iterator       i,
                           ArgumentList::const_iterator const end) = 0;

    virtual
    Signature const & getSignature() const = 0;
};

}

#endif