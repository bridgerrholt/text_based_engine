/// @file string_formatter.cpp
/// Definition of the class dep::StringFormatter.

#include "string_formatter.h"

#include <algorithm> 
#include <functional> 
#include <cctype>

namespace dep {

StringFormatter::StringFormatter(std::locale const & locale,
                                 std::string         contents) :
  locale_  (locale),
  contents_(std::move(contents))
{

}



std::string
StringFormatter::str() const
{
  return contents_;
}



std::string const &
StringFormatter::strRef() const
{
  return contents_;
}



std::string
StringFormatter::moveOut()
{
  std::string toReturn { std::move(contents_) };
  return toReturn;
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
  if (!contents_.empty()) {
    auto begin   = contents_.begin();
    auto eraseTo = begin;

    while (eraseTo != contents_.end() &&
           std::isspace(*eraseTo, locale_)) {

      ++eraseTo;
    }

    if (eraseTo != begin)
      contents_.erase(begin, eraseTo);
  }
  
  return *this;
}


StringFormatter&
StringFormatter::trimRight()
{
  if (!contents_.empty()) {
    auto end       = contents_.end();
    auto eraseFrom = end;

    do {
      --eraseFrom;

    } while (eraseFrom != contents_.begin() &&
             std::isspace(*eraseFrom, locale_));

    ++eraseFrom;

    if (eraseFrom != end)
      contents_.erase(eraseFrom, end);
  }
  
  return *this;
}


StringFormatter&
StringFormatter::trim()
{
  if (contents_.empty())
    return *this;
  else
   return this->trimLeft().trimRight();
}



}