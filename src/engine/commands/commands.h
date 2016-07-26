/// @file commands.h
/// Declarations of the command classes.

#ifndef TEXT_BASED_ENGINE_ENGINE_COMMANDS_COMMANDS_H
#define TEXT_BASED_ENGINE_ENGINE_COMMANDS_COMMANDS_H

#include <dep/of_dynamic.h>

#include "../command.h"
#include "../argument.h"

namespace tbe {
  namespace commands {
  
template <Command c>
class BasicCommand : public CommandBase
{
  public:
    Command getKindId() const { return c; }

    CommandBase::Signature const &
    getSignature() const { return signature_; }

  private:
    InputInfo execute(GameStateMap &                     stateMap,
                      ArgumentList::const_iterator       i,
                      ArgumentList::const_iterator const end);

    static CommandBase::Signature signature_;
};


typedef BasicCommand<SET> Set;


template <>
CommandBase::Signature
Set::signature_ = { ArgumentBase::OPTION, ArgumentBase::OBJECT };


template <>
InputInfo
Set::execute(GameStateMap &                     stateMap,
             ArgumentList::const_iterator       i,
             ArgumentList::const_iterator const end)
{
  auto var = stateMap.var(dep::ofDynamic<arg_types::Option>(i->get())->data);
  ++i;

  if (var) {
    auto setTo = dep::ofDynamic<arg_types::Object>(i->get());
    if (var->get()->getKind() == setTo->data->getKind()) {
      var->reset(std::move(setTo->data.get()));
      return VALID;
    }
  }
  
  return INVALID;
}


  }
}

#endif