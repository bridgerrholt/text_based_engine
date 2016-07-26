/// @file game_state.h
/// Declarations of the class tbe::GameState.

#ifndef TEXT_BASED_ENGINE_ENGINE_GAME_STATE_H
#define TEXT_BASED_ENGINE_ENGINE_GAME_STATE_H

#include <string>
#include <vector>
#include <unordered_map>

#include "../sql_support/dynamic_type.h"

namespace tbe {

class GameState
{
  public:
    void pushVariable(std::string          name);

    bool hasVariable  (std::string const & name);

    void eraseVariable(std::string const & name);

  private:
    typedef std::vector<std::string> StringList;

    StringList::iterator findVariable(std::string const & name);

    StringList variables_;
    StringList commands_;

};

}

#endif