/// @file game_state_map.h
/// Declaration of the class tbe::GameStateMap.

/// @class tbe::GameStateMap
/// Provides a dynamic global and local variable system.
/// Basically there's a collection of global variables and a collection of local variables.

#ifndef TEXT_BASED_ENGINE_ENGINE_GAME_STATE_MAP_H
#define TEXT_BASED_ENGINE_ENGINE_GAME_STATE_MAP_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "../sql_support/common/var_list.h"
#include "../sql_support/types/basic_type.h"

#include "game_state.h"

namespace tbe {

class GameStateMap
{
  public:
    /// Maps variable names to their values.
    typedef std::unordered_map <
      std::string, sql::DynamicVar
    > VariableMap;


    /// A simple list of GameState objects.
    typedef std::vector <GameState> StateList;

    typedef          std::string          StateName;
    typedef typename StateList::size_type StateId;

    /// Maps state names to their IDs.
    typedef std::unordered_map<
      StateName, StateId
    > StateNameMap;



    void insertGlobalVar(typename VariableMap::key_type          key,
                         typename VariableMap::mapped_type       value);
    
    void insertGlobalVar(typename VariableMap::key_type          key,
                         typename VariableMap::mapped_type::element_type*
                                                                 value);

    template <class T, class V>
    void insertGlobalVar(typename VariableMap::key_type          key,
                                  V                              value);


    void insertLocalVar (typename VariableMap::key_type          key,
                         typename VariableMap::mapped_type       value,
                         std::vector<StateId> const &            states);

    void insertLocalVar (typename VariableMap::key_type          key,
                         typename VariableMap::mapped_type::element_type*
                                                                 value,
                         std::vector<StateId> const &            states);

    

    void eraseGlobalVar (typename VariableMap::key_type          key);
    void eraseLocalVar  (typename VariableMap::key_type          key);
    
    typename VariableMap::mapped_type &
         globalVar      (typename VariableMap::key_type          key);

    typename VariableMap::mapped_type &
         localVar       (typename VariableMap::key_type          key);

    /// @return Is nullptr on failure.
    typename VariableMap::mapped_type *
         var            (typename VariableMap::key_type          key);


    StateId insertGameState  (StateName const & stateName);
    StateId getStateId       (StateName const & stateName);

    bool    checkStateExists (StateName const & stateName);
    bool    checkStateExists (StateId           stateId);

    void    verifyStateExists(StateName const & stateName);
    void    verifyStateExists(StateId           stateId);

    void    setState         (StateName const & stateName);
    void    setState         (StateId           stateId);


  private:
    typename VariableMap::mapped_type *
         localVarTry    (typename VariableMap::key_type          key);

    VariableMap  globalVars_;
    VariableMap  localVars_;

    StateNameMap gameStateNames_;
    StateList    gameStates_;
    StateId      currentState_ = 0;
};


class GameStateMapV2
{
  public:
    
    
};


template <class T, class V>
void
GameStateMap::insertGlobalVar(typename VariableMap::key_type key,
                                       V                     value)
{
  insertGlobalVar(key, new T { std::move(value) });
}

}

#endif