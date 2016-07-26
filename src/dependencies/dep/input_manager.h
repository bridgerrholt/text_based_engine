/// @file input_manager.h
/// Declaration of the class dep::InputManager.

#ifndef _DEPENDENCIES_DEP_INPUT_MANAGER_H
#define _DEPENDENCIES_DEP_INPUT_MANAGER_H

#include <iostream>
#include <locale>
#include <string>

// Include is preferred over forward declaration because InputManager relies on StringFormatter so
// much that consumers of this file will most likely need the full declaration.
#include "string_formatter.h" 
                              
namespace dep {
  
/// Reads out standard input.
class InputManager
{
  public:
    /// Primary constructor.
    /// @param[in] localeSet The program-wide locale to be
    ///                      passed to returned StringFormatter objects.
    InputManager(std::locale const & localeSet,
                 std::string         promptTextSet = "> ");

    /// Reads the user input into a StringFormatter.
    /// @return The StringFormatter constructed from the string.
    StringFormatter get() const;

    /// @param inputString[out] Used for getting the standard input, passed instead of
    ///                         having the function create one upon call.
    StringFormatter get(std::string & inputString) const;


    /// Reads the user input into a string.
    /// @return The string that standard input was read into.
    std::string getPure() const;

    /// @param[out] inputString Used for getting the standard input.
    void        getPure(std::string & inputString) const;


    /// Displays a prompt (@ref promptText) and then gets the input.
    StringFormatter prompt() const;
    
    /// Trims the input.
    std::string promptClean() const;


    /// The program-wide locale, is currently only used to create StringFormatter objects.
    std::locale const & locale;

    /// Displayed at the beginning of prompt functions.
    std::string promptText;


  private:

};
  
}

#endif