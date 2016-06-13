#include "format_string.h"

#include <algorithm> 
#include <functional> 
#include <cctype>

namespace dep {

FormatString::FormatString(std::locale const & locale,
                           com::StringRef      contents) :
  locale_  (locale),
  contents_(contents)
{

}



std::string
FormatString::str() const
{
  return contents_;
}

std::string
str(FormatString const & formatString)
{
  return formatString.str();
}


// Format functions

// Trim family
FormatString&
FormatString::trimLeft()
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


FormatString&
FormatString::trimRight()
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


FormatString&
FormatString::trim()
{
  return this->trimLeft().trimRight();
}



}