/// @file input_manager.cpp
/// Definition of the dep::InputManager class.

#include "input_manager.h"

namespace dep {

InputManager::InputManager(std::locale const & locale) :
  locale_(locale)
{

}



StringFormatter
InputManager::get()
{
  std::string inputString;
  return get(inputString);
}


StringFormatter
InputManager::get(std::string & inputString)
{
  getPure(inputString);
  return StringFormatter(locale_, inputString);
}



std::string
InputManager::getPure()
{
  std::string inputString;
  getPure(inputString);
  
  return inputString;
}


void
InputManager::getPure(std::string & inputString)
{
  std::getline(std::cin, inputString);
}



}