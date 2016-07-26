/// @file print_line.h
/// Declaration of the overloaded function template dep::printLine().

#ifndef _DEPENDENCIES_DEP_PRINT_LINE_H
#define _DEPENDENCIES_DEP_PRINT_LINE_H

#include <iostream>

namespace dep {

/// Outputs the given string to the given output, followed by a newline character.
/// The stream is also flushed after outputting.
/// @tparam T The type of object to output. Any type works as long as it can be outputted
///           to @p S.
/// @tparam S The type of object to output to.
/// @param[in] toPrint  Is outputted to @p outStream with a newline character after.
/// @param[in] outStram The stream to output to.
template <class T, class S = std::ostream>
void printLine   (T const & toPrint,
                  S       & outStream = std::cout)
{
  outStream << toPrint << std::endl;
}



/// Outputs to std::cerr.
template <class T>
void printLineErr(T const & toPrint)
{
  printLine(toPrint, std::cerr);
}



/// Outputs to std::clog.
template <class T>
void printLineLog(T const & toPrint)
{
  printLine(toPrint, std::clog);
}



}

#endif
