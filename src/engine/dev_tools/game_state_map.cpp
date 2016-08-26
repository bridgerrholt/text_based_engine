/// @file game_state_map.cpp
/// Definition of the class tbe::GameStateMap.

#include "game_state_map.h"

#include <cassert>
#include <stdexcept>

#include "commands/commands.h"


namespace {

std::string
formatGameStateName(std::string const & stateName)
{
  return "Game state (" + stateName + ")";
}

std::string
invalidStateMessage(std::string const & stateName)
{
  return formatGameStateName(stateName) + " doesn't exist";
}

}

namespace tbe {

void
GameStateMap::insertGlobalVar(typename VariableMap::key_type    key,
                              typename VariableMap::mapped_type value)
{
  assert(globalVars_.count(key) == 0);

  globalVars_.insert({ std::move(key), std::move(value) });
}


void
GameStateMap::insertGlobalVar(typename VariableMap::key_type          key,
                              typename VariableMap::mapped_type::element_type*
                                                                      value)
{
  insertGlobalVar(std::move(key), VariableMap::mapped_type { value });
}



void
GameStateMap::insertLocalVar(typename VariableMap::key_type            key,
                             typename VariableMap::mapped_type         value,
                             std::vector<StateId> const &              states)
{
  assert(localVars_.count(key) == 0);

  localVars_.insert({ key, std::move(value) });

  for (auto const & i : states) {
    gameStates_[i].pushVariable(key);
  }
}


void
GameStateMap::insertLocalVar(typename VariableMap::key_type          key,
                             typename VariableMap::mapped_type::element_type*
                                                                     value,
                             std::vector<StateId> const &            states)
{
  insertLocalVar(std::move(key), VariableMap::mapped_type { value }, states);
}

    

void
GameStateMap::eraseGlobalVar(typename VariableMap::key_type key)
{
  globalVars_.erase(key);
}



void
GameStateMap::eraseLocalVar(typename VariableMap::key_type key)
{
  for (auto & i : gameStates_)
    i.second.eraseVariable(key);

  localVars_.erase(key);
}


typename GameStateMap::VariableMap::mapped_type &
GameStateMap::globalVar(typename VariableMap::key_type key)
{
  return globalVars_.at(key);
}



typename GameStateMap::VariableMap::mapped_type &
GameStateMap::localVar(typename VariableMap::key_type key)
{
  return *localVarTry(key);
}



typename GameStateMap::VariableMap::mapped_type *
GameStateMap::var(typename VariableMap::key_type key)
{
  auto local = localVarTry(key);

  if (local)
    return local;

  else if (globalVars_.count(key) != 0)
    return &globalVars_[key];
  
  else
    return nullptr;
}



typename GameStateMap::VariableMap::mapped_type *
GameStateMap::localVarTry(typename VariableMap::key_type key)
{
  if (gameStates_.size() == 0)
    return nullptr;

  if (gameStates_.at(currentState_).hasVariable(key) &&
      localVars_.count(key) != 0) {
    return &localVars_[key];
  }

  return nullptr;
}



GameStateMap::StateId
GameStateMap::insertGameState(StateName const & stateName)
{
  if (checkStateExists(stateName))
    throw std::runtime_error("State (" + stateName +") already exists");

  gameStateNames_.insert({stateName, gameStates_.size()});
  gameStates_.emplace_back();
}



GameStateMap::StateId
GameStateMap::getStateId(StateName const & stateName)
{
  if (!checkStateExists(stateName))
    throw std::runtime_error("State (" + stateName + ") doesn't exist");

  return gameStateNames_[stateName];
}




bool   
GameStateMap::checkStateExists(StateName const & stateName)
{
  return (gameStateNames_.count(stateName) != 0);
}


bool   
GameStateMap::checkStateExists(StateId stateId)
{
  return (stateId < stateIdCount_);
}



void
GameStateMap::verifyStateExists(StateName const & stateName)
{

}


void
GameStateMap::verifyStateExists(StateId stateId)
{


}



void   
GameStateMap::setState(StateName const & stateName)
{


}



void   
GameStateMap::setState(StateId stateId)
{


}



}
