/// @file state_map.h
/// Declaration of the class tbe::StateMap.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_STATE_MAP_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_STATE_MAP_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "types/object_ptr.h"
#include "command.h"

namespace tbe {
	namespace dev_tools {


/// Contains and manages commands and variables which may be accessed through
/// specified "states".
class StateMap
{
	public:
		template <class T, class K = std::string>
		using MapType = std::unordered_map<K, T>;

		using VariableMap = MapType<types::ObjectPtr>;
		using CommandMap  = MapType<std::unique_ptr<CommandBase> >;


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
				using Container = std::vector<std::string>;

				State();
				State(Container commands,
				      Container variables);

				Container const & getCommands()  const { return commands_; }
				Container const & getVariables() const { return variables_; }

			private:
				Container commands_;
				Container variables_;
		};

		using StateContainer = std::unordered_map<std::string, State>;

		StateMap();
		StateMap(Scope shared, Scope global);

		void pushState(StateContainer::key_type name, State state);
		void setState (StateContainer::key_type name);

		VariableMap::mapped_type *
		getVariable(StateContainer::key_type const & name);

		CommandMap::mapped_type::element_type *
		getCommand(StateContainer::key_type const & name);


		void pushGlobalVariable(VariableMap::key_type    name,
		                        VariableMap::mapped_type variable);

		void pushSharedVariable(VariableMap::key_type    name,
		                        VariableMap::mapped_type variable);

		void pushGlobalCommand(CommandMap::key_type    name,
		                       CommandMap::mapped_type command);

		void pushSharedCommand(CommandMap::key_type    name,
		                       CommandMap::mapped_type command);


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

		template <class T>
		void genericPush(typename MapType<T>::key_type name,
		                 T                             object,
		                 MapType<T>                  & map,
		                 std::string const           & objectDescription);
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



template <class T>
void
StateMap::genericPush(typename MapType<T>::key_type name,
                      T                             object,
                      MapType<T>                  & map,
                      std::string const           & objectDescription)
{
	auto i = map.find(name);

	if (i != map.end()) {
		throw std::runtime_error(
			objectDescription + " \"" + name + "\" already exists"
		);
	}

	map.emplace(std::move(name), std::move(object));
}


	}
}

#endif