/// @file state_map.cpp
/// Definition of the class tbe::StateMap

#include "state_map.h"

#include <stdexcept>

namespace tbe {
  namespace dev_tools {

void swap(StateMap& first, StateMap& second)
{
	using std::swap;

	swap(first.states_,       second.states_);
	swap(first.currentState_, second.currentState_);

	swap(first.shared_,       second.shared_);
	swap(first.global_,       second.global_);
}


void swap(StateMap::Scope & first, StateMap::Scope & second)
{
	using std::swap;

	swap(first.variables, second.variables);
	swap(first.commands,  second.commands);
}


StateMap::Scope::Scope() {}

StateMap::Scope::Scope(VariableMap variablesSet,
	                     CommandMap  commandsSet) :
	variables(variablesSet),
	commands(commandsSet) {}

StateMap::Scope::Scope(StateMap::Scope && other)
{
	swap(*this, other);
}


StateMap::Scope &
StateMap::Scope::operator=(Scope other)
{
  swap(*this, other);
	return *this;
}


StateMap::StateMap()
{

}


StateMap::StateMap(StateMap && other)
{
	swap(*this, other);
}



StateMap::StateMap(Scope shared, Scope global) :
  shared_(std::move(shared)),
  global_(std::move(global))
{

}



StateMap&
StateMap::operator=(StateMap other)
{
	swap(*this, other);

	return *this;
}



void
StateMap::pushState(StateIdType name, State state)
{
  if (states_.find(name) != states_.end())
    throw std::runtime_error("State (" + name + ") already exists");

  else {
    verifyState(state);
		if (states_.size() == 0)
			currentState_ = name;
    states_.emplace(std::move(name), std::move(state));
  }
}



void
StateMap::setCurrentState(StateIdType name)
{
  if (states_.find(name) == states_.end())
    throw std::runtime_error("State (" + name + ") doesn't exist");

  else
    currentState_ = std::move(name);
}


StateMap::StateIdType const &
StateMap::getCurrentState()
{
  return currentState_;
}



StateMap::VariableMap::mapped_type *
StateMap::getVariable(StateIdType const & name)
{
  return getObject(name, states_.at(currentState_).getCommands(),
                   shared_.variables, global_.variables);
}



StateMap::CommandMap::mapped_type::element_type *
StateMap::getCommand(StateIdType const & name)
{
  auto * i = getObject(name, states_.at(currentState_).getCommands(),
                     shared_.commands, global_.commands);

  if (i)
    return i->get();
  else
    return nullptr;
}



void
StateMap::pushGlobalVariable(NameType     name,
                             VariableType variable)
{
  genericPush(std::move(name), std::move(variable),
    global_.variables, "Global variable");
}


void
StateMap::pushSharedVariable(NameType     name,
                             VariableType variable)
{
  genericPush(std::move(name), std::move(variable),
    shared_.variables, "Shared variable");
}



void
StateMap::pushGlobalCommand(NameType    name,
                            CommandType command)
{
  genericPush(std::move(name), std::move(command),
    global_.commands, "Global command");
}


void
StateMap::pushSharedCommand(NameType    name,
                            CommandType command)
{
  genericPush(std::move(name), std::move(command),
    shared_.commands, "Shared command");
}



void
StateMap::clear()
{
	*this = StateMap();
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
}