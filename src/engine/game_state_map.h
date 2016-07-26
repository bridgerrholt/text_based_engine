/// @file game_state_map.h
/// Declaration of the class tbe::GameStateMap.

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
    typedef std::unordered_map <
      std::string, sql::DynamicVar
    > VariableMap;

    typedef std::unordered_map <
      std::size_t, GameState
    > StateMap;
    

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
                         std::vector<
                           typename StateMap ::key_type> const & states);

    void insertLocalVar (typename VariableMap::key_type          key,
                         typename VariableMap::mapped_type::element_type*
                                                                 value,
                         std::vector<
                           typename StateMap ::key_type> const & states);
    

    void eraseGlobalVar (typename VariableMap::key_type          key);
    void eraseLocalVar  (typename VariableMap::key_type          key);
    
    typename VariableMap::mapped_type &
         globalVar      (typename VariableMap::key_type          key);

    typename VariableMap::mapped_type &
         localVar       (typename VariableMap::key_type          key);

    /// @return Is nullptr on failure.
    typename VariableMap::mapped_type *
         var            (typename VariableMap::key_type          key);


  private:
    typename VariableMap::mapped_type *
         localVarTry    (typename VariableMap::key_type          key);

    VariableMap        globalVars_;
    VariableMap        localVars_;

    StateMap           gameStates_;
    StateMap::key_type currentState_ = 0;

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