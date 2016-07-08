/// @file where_clause_string.cpp
/// Definition of the inherited class tbe::sql::WhereClauseString.

#include "where_clause_string.h"

#include <utility> // std::move

namespace tbe {
  namespace sql {

WhereClauseString::WhereClauseString(std::string textSet) :
  text(std::move(textSet))
{

}



std::string
WhereClauseString::getText() const
{
  return text;
}



bool
WhereClauseString::hasConditions() const
{
  return (text != "");
}



  }
}