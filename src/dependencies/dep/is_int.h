/** @file is_int.h
    Declaration of the dep::isInt function.


    @fn dep::isInt
    Determines whether a given string represents an integer or not.
    Does not strip the passed string of whitespace.

    @param str The given string.
    @return Whether @p str represents an integer.
*/

#ifndef _DEPENDENCIES_DEP_IS_INT_H
#define _DEPENDENCIES_DEP_IS_INT_H

#include <com/string_ref.h>

namespace dep {

bool isInt(com::StringRef str);

}

#endif