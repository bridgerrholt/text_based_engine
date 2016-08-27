/// @file state_map.cpp
/// Definition of the class tbe::StateMap

#include "state_map.h"

#include <stdexcept>

namespace tbe {

StateMap::StateMap(Scope shared, Scope global) :
  shared_(std::move(shared)),
  global_(std::move(global))
{

}



void
StateMap::pushState(StateContainer::key_type name, State state)
{
  if (states_.find(name) != states_.end())
    throw std::runtime_error("State (" + name + ") already exists");

  else {
    verifyState(state);
    states_.insert({std::move(name), std::move(state)});
  }
}



void
StateMap::setState(StateContainer::key_type name)
{
  if (states_.find(name) == states_.end())
    throw std::runtime_error("State (" + name + ") doesn't exist");

  else
    currentState_ = std::move(name);
}



StateMap::CommandMap::mapped_type::element_type *
StateMap::getCommand(StateContainer::key_type const & name)
{
  auto i = getObject(name, states_[currentState_].getCommands(),
                     shared_.commands, global_.commands);

  if (i)
    return i->get();
  else
    return nullptr;
}



StateMap::VariableMap::mapped_type *
StateMap::getVariable(StateContainer::key_type const & name)
{
  return getObject(name, states_[currentState_].getCommands(),
                   shared_.variables, global_.variables);
}



void
StateMap::verifyState(State const & state)
{
  for (auto const & i : state.getCommands()) {
    if (shared_.commands.find(i) == shared_.commands.end() ||
        global_.commands.find(i) == global_.commands.end()) {

      throw std::runtime_error("No such command: " + i);
    }
  }

  for (auto const & i : state.getVariables()) {
    if (shared_.variables.find(i) == shared_.variables.end() ||
        global_.variables.find(i) == global_.variables.end()) {

      throw std::runtime_error("No such variable: " + i);
    }
  }
}




StateMap::State::State()
{

}


StateMap::State::State(Container commands,
                       Container variables) :
  commands_ (commands),
  variables_(variables)
{

}

}