#include "input_manager.h"

namespace dep {

InputManager::InputManager(std::locale const & locale) :
  locale_(locale)
{

}



FormatString
InputManager::get()
{
  std::string inputString;
  return get(inputString);
}


FormatString
InputManager::get(std::string & inputString)
{
  std::getline(std::cin, inputString);
  return FormatString(locale_, inputString);
}



}