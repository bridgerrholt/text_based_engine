/// @file string_formatter.cpp
/// Definition of the dep::StringFormatter class.

#include "string_formatter.h"

#include <algorithm> 
#include <functional> 
#include <cctype>

namespace dep {

StringFormatter::StringFormatter(std::locale const & locale,
                                 com::StringRef      contents) :
  locale_  (locale),
  contents_(contents)
{

}



std::string
StringFormatter::str() const
{
  return contents_;
}


std::string
str(StringFormatter const & stringFormatter)
{
  return stringFormatter.str();
}



// Format functions

// Trim family
StringFormatter&
StringFormatter::trimLeft()
{
  auto begin   = contents_.begin();
  auto eraseTo = begin;

  while (eraseTo != contents_.end() &&
         std::isspace(*eraseTo, locale_)) {

    ++eraseTo;
  }

  if (eraseTo != begin)
    contents_.erase(begin, eraseTo);
  
  return *this;
}


StringFormatter&
StringFormatter::trimRight()
{
  auto end       = contents_.end();
  auto eraseFrom = end;

  do {
    --eraseFrom;

  } while (eraseFrom != contents_.begin() &&
           std::isspace(*eraseFrom, locale_));

  ++eraseFrom;

  if (eraseFrom != end)
    contents_.erase(eraseFrom, end);
  
  return *this;
}


StringFormatter&
StringFormatter::trim()
{
  return this->trimLeft().trimRight();
}



}