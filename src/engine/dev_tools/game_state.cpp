/// @file game_state.cpp
/// Definition of the class tbe::GameState.

#include "game_state.h"

#include <cassert>
#include <algorithm>

namespace tbe {

void
GameState::pushVariable(std::string name)
{
  if (!hasVariable(name))
    variables_.push_back(std::move(name));
}



bool
GameState::hasVariable(std::string const & name)
{
  return (findVariable(name) != variables_.end());
}



void
GameState::eraseVariable(std::string const & name)
{
  auto const i = findVariable(name);

  if (i != variables_.end())
    variables_.erase(i);
}



GameState::StringList::iterator
GameState::findVariable(std::string const & name)
{
  return std::find(variables_.begin(), variables_.end(), name);
}



}
