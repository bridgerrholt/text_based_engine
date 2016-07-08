/// @file input_manager.h
/// Declaration of the class dep::InputManager.

/// @class dep::InputManager
/// Reads out user input from standard input.

#ifndef _DEPENDENCIES_DEP_INPUT_MANAGER_H
#define _DEPENDENCIES_DEP_INPUT_MANAGER_H

#include <iostream>
#include <locale>
#include <string>

// Include is preferred over forward declaration because InputManager relies on StringFormatter so
// much that consumers of this file will most likely need the full declaration.
#include "string_formatter.h" 
                              
namespace dep {

class InputManager
{
  public:
    /// Primary constructor.
    /// @param[in] locale The program-wide locale to be
    ///                   passed to returned StringFormatter objects.
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