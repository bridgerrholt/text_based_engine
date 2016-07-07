/** @file string_formatter.h
    Declaration of the dep::StringFormatter class and helper functions.

    @class dep::StringFormatter
    Contains methods for chaining together different formatting functions on a specific string.
*/

#ifndef _DEPENDENCIES_DEP_STRING_FORMATTER_H
#define _DEPENDENCIES_DEP_STRING_FORMATTER_H

#include <locale>

#include <com/string_ref.h>

namespace dep {

class StringFormatter
{
  public:
    /// Primary constructor.
    /// @param locale   The program-wide locale used.
    /// @param contents The string to be formatted.
    StringFormatter(std::locale const & locale,
                     com::StringRef      contents);

    /// Copies the string's current state.
    /// @return The copied version of @ref contents_.
    std::string str() const;

    /// Removes all whitespace at the beginning of the string.
    StringFormatter& trimLeft();

    /// Removes all whitespace at the end of the string.
    StringFormatter& trimRight();

    /// Removes all whitespace at both the beginning and the end of the string.
    StringFormatter& trim();


  private:
    /// Reference to the program-wide locale.
    std::locale const & locale_;

    /// The string being formatted.
    std::string contents_;
};


/** Returns the string of a StringFormatter's current state.
    In other words, does exactly what StringFormatter::str does.
    This function may be preferred for clarity.

    @param StringFormatter Reference to the target StringFormatter.
    @return The string contents (@ref StringFormatter::contents_) of the StringFormatter.
*/
std::string str(StringFormatter const & stringFormatter);


  
}

#endif