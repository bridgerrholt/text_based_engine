/// @file where_clause.cpp
/// Definition of the inherited class tbe::sql::ExpressionString.

#include "expression_string.h"

#include <utility> // std::move

namespace tbe {
  namespace sql {

ExpressionString::ExpressionString(std::string textSet) :
  text(std::move(textSet))
{

}



std::string
ExpressionString::getText()
{
  return text;
}



  }
}