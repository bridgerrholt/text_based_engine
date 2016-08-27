/// @file state_map.cpp
/// Definition of the class tbe::StateMap

#include "state_map.h"

#include <stdexcept>

namespace tbe {

StateMap::StateMap(Scope shared, Scope global) :
  shared_(shared),
  global_(global)
{

}



void
StateMap::pushState(std::string name, State state)
{
  if (states_.find(name) != states_.end())
    throw std::runtime_error("State (" + name + ") already exists");

  else {
    verifyState(state);
    states_.insert({name, state});
  }
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

}