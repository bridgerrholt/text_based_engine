/** @file input_manager.h
    Declaration of the dep::InputManager class.

    @class dep::InputManager
    Reads out user input from standard input.
*/

#ifndef _DEPENDENCIES_DEP_INPUT_MANAGER_H
#define _DEPENDENCIES_DEP_INPUT_MANAGER_H

#include <iostream>
#include <locale>

#include "string_formatter.h" // Include is preferred over forward declaration because
                              // almost all of InputManager's methods return a StringFormatter.

namespace dep {

class InputManager
{
public:
  /// Primary constructor.
  /// @param locale The program-wide locale to be passed to returned StringFormatter objects.
  InputManager(std::locale const & locale);

  /// Reads the user input into a StringFormatter.
  /// @return The StringFormatter constructed from the string.
  StringFormatter get();

  /// @param inputString[out] Used for getting the standard input, passed instead of
  ///                         having the function create one upon call.
  StringFormatter get(std::string & inputString);


  /// Reads the user input into a string.
  /// @return The string that standard input was read into.
  std::string getPure();

  /// @param[out] inputString Used for getting the standard input.
  void        getPure(std::string & inputString);


private:
  /// The program-wide locale, is currently only used to create StringFormatter objects.
  std::locale const & locale_;

};

  
}

#endif