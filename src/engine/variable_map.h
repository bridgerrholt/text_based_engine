/// @file variable_map.h
/// Declarations of the class tbe::VariableMap.

#ifndef TEXT_BASED_ENGINE_ENGINE_VARIABLE_MAP_H
#define TEXT_BASED_ENGINE_ENGINE_VARIABLE_MAP_H

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "../sql_support/dynamic_type.h"

namespace tbe {

class VariableMap
{
  public:
    typedef std::unordered_map<std::string,
                               std::unique_ptr<sql::DynamicType> > Container;
    
    void insertVariable(typename Container::key_type,
                        typename Container::mapped_type);

    void insertVariable(typename Container::key_type,
                        typename Container::mapped_type,
                        std::vector<);

  private:

};

}

#endif