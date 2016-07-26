/// @file input_manager.cpp
/// Definition of the class dep::InputManager.

#include "input_manager.h"

namespace dep {

InputManager::InputManager(std::locale const & localeSet,
                           std::string         promptTextSet) :
  locale(localeSet),

  promptText(promptTextSet)
{

}



StringFormatter
InputManager::get() const
{
  std::string inputString;
  return get(inputString);
}


StringFormatter
InputManager::get(std::string & inputString) const
{
  getPure(inputString);
  return StringFormatter(locale, inputString);
}



std::string
InputManager::getPure() const
{
  std::string inputString;
  getPure(inputString);
  
  return inputString;
}


void
InputManager::getPure(std::string & inputString) const
{
  std::getline(std::cin, inputString);
}



StringFormatter
InputManager::prompt() const
{
  std::cout << promptText;
  return get();
}



std::string
InputManager::promptClean() const
{
  return prompt().trim().str();
}



}