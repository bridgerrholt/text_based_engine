/// @file load_to_string.h
/// Declaration of the dep::loadToString() functions.

#ifndef _DEPENDENCIES_DEP_LOAD_TO_STRING_H
#define _DEPENDENCIES_DEP_LOAD_TO_STRING_H

#include <com/string_ref.h>

namespace dep {

/** Reads the given file to a string.

    @param[in] fileName The full path and name of the target file.
    @return The constructed string with the file's contents.
*/
std::string loadToString(com::StringRef fileName);

/// @param[out] returnString The user-created string that the file gets read to.
void        loadToString(com::StringRef fileName, 
                         std::string&   returnString);

}

#endif
