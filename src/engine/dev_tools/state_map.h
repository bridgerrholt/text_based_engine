/// @file state_map.h
/// Declaration of the class tbe::StateMap.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_STATE_MAP_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_STATE_MAP_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "../sql_support/dynamic_type.h"
#include "command.h"

namespace tbe {

/// Contains and manages commands and variables which may be accessed through
/// specified "states".
class StateMap
{
  public:
    template <class T, class K = std::string>
    using MapType = std::unordered_map<K, T>;

    typedef MapType<sql::DynamicVar>               VariableMap;
    typedef MapType<std::unique_ptr<CommandBase> > CommandMap;


    /// Contains variables and commands meant to be in a specific scope.
    class Scope
    {
      public:
        VariableMap variables;
        CommandMap  commands;
    };


    /// Contains references to useable commands and variables.
    class State
    {
      public:
        typedef std::vector<std::string> Container;

        State();
        State(Container commands,
              Container variables);

        Container const & getCommands()  const { return commands_; }
        Container const & getVariables() const { return variables_; }

      private:
        Container commands_;
        Container variables_;
    };

    typedef std::unordered_map<std::string, State> StateContainer;


    StateMap(Scope shared, Scope global);

    void pushState(StateContainer::key_type name, State state);
    void setState(StateContainer::key_type name);
    
    CommandMap::mapped_type::element_type *
    getCommand(StateContainer::key_type const & name);

    VariableMap::mapped_type *
    getVariable(StateContainer::key_type const & name);


  private:
    StateContainer           states_;
    StateContainer::key_type currentState_;

    void verifyState(State const & state);


    Scope shared_;
    Scope global_;

    template <class T>
    T *
    getObject(StateContainer::key_type const & name,
              State::Container         const & allowedNames,
              MapType<T>                     & shared,
              MapType<T>                     & global);

};



template <class T>
T *
StateMap::getObject(StateContainer::key_type const & name,
                    State::Container         const & allowedNames,
                    MapType<T>                     & shared,
                    MapType<T>                     & global)
{
  for (auto const & i : allowedNames) {
    if (name == i) {
      return &shared[name];
    }
  }


  // Not in the shared pool, try to find in the global pool.
  auto command = global.find(name);

  if (command != global.end())
    return &command->second;


  // Doesn't exist.
  return nullptr;
}



}

#endif