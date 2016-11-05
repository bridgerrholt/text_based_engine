/// @file state_map.h
/// Declaration of the class tbe::dev_tools::StateMap.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_STATE_MAP_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_STATE_MAP_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "types/object_ptr.h"
#include "commands/command_ptr.h"

namespace tbe {
	namespace dev_tools {


/// Contains and manages commands and variables which may be accessed through
/// specified "states".
class StateMap
{
	public:
		using StateIdType = std::string;
		using NameType = std::string;
		using VariableType = types::ObjectPtr;
		using CommandType  = commands::CommandPtr;

		template <class T, class K = NameType>
		using MapType = std::unordered_map<K, T>;

		using VariableMap = MapType<VariableType>;
		using CommandMap  = MapType<CommandType>;


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
				using Container = std::vector<NameType>;

				State();
				State(Container commands,
				      Container variables);

				Container const & getCommands()  const { return commands_; }
				Container const & getVariables() const { return variables_; }

			private:
				Container commands_;
				Container variables_;
		};

		using StateContainer = std::unordered_map<StateIdType, State>;

		
		friend void swap(StateMap& first, StateMap& second);

		StateMap();
		StateMap(Scope shared, Scope global);
		~StateMap() {}

		StateMap& operator=(StateMap other);


		void pushState(StateIdType name, State state);
		void setCurrentState(StateIdType name);
		StateIdType const & getCurrentState();
		
		VariableType *
		getVariable(StateIdType const & name);

		template <class T>
		typename T::DataType &
		getVariableValue(StateIdType const & name);

		CommandType::element_type *
		getCommand(StateIdType const & name);


		void pushGlobalVariable(NameType    name,
		                        VariableType variable);

		void pushSharedVariable(NameType    name,
		                        VariableType variable);

		void pushGlobalCommand(NameType    name,
		                       CommandType command);

		void pushSharedCommand(NameType    name,
		                       CommandType command);

		void clear();


	private:
		StateContainer states_;
		StateIdType    currentState_;

		void verifyState(State const & state);


		Scope shared_;
		Scope global_;

		template <class T>
		T *
		getObject(NameType         const & name,
		          State::Container const & allowedNames,
		          MapType<T>             & shared,
		          MapType<T>             & global);

		/// @param objectDescription Used in error messages to describe what kind of
		///                          object caused the error.
		template <class T>
		void genericPush(typename MapType<T>::key_type name,
		                 T                             object,
		                 MapType<T>                  & map,
		                 std::string const           & objectDescription);
};


template <class T>
typename T::DataType &
StateMap::getVariableValue(StateIdType const & name)
{
	auto* variable = getVariable(name);
	assert(variable);

	return dep::ofDynamic<T>(variable->get())->data;
}



template <class T>
T *
StateMap::getObject(NameType         const & name,
                    State::Container const & allowedNames,
                    MapType<T>             & shared,
                    MapType<T>             & global)
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