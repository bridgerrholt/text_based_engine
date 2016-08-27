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

class StateMap
{
  public:
    template <class T, class K = std::string>
    using MapType = std::unordered_map<K, T>;

    typedef MapType<sql::DynamicVar>               VariableMap;
    typedef MapType<std::unique_ptr<CommandBase> > CommandMap;

    class Scope
    {
      public:
        VariableMap variables;
        CommandMap  commands;
    };


    class State
    {
      public:
        typedef std::vector<std::string> Container;

        State(Container commands,
              Container variables);

        Container const & getCommands()  const { return commands_; }
        Container const & getVariables() const { return variables_; }

      private:
        Container commands_;
        Container variables_;
    };


    StateMap(Scope shared, Scope global);

    void pushState(std::string name, State state);


  private:
    typedef std::unordered_map<std::string, State> StateContainer;
    StateContainer           states_;
    StateContainer::key_type currentState_;

    void verifyState(State const & state);

    Scope shared_;
    Scope global_;
};

}

#endif