/// @file game_state_map.cpp
/// Definition of the class tbe::GameStateMap.

#include "game_state_map.h"

#include "commands/commands.h"

#include <cassert>

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
                             std::vector<
                               typename StateMap ::key_type> const &   states)
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
                             std::vector<
                               typename StateMap ::key_type> const &   states)
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



}
