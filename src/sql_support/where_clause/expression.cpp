/// @file expression.cpp
/// Definition of the inherited class tbe::sql::Expression.

#include "expression.h"

#include <utility> // std::move

namespace tbe {
  namespace sql {

Expression::Expression(ColumnInfo const & columnSet,
                       std::string        operatorTextSet,
                       std::string        valueTextSet) :
  column      (columnSet),
  operatorText(std::move(operatorTextSet)),
  valueText   (std::move(valueTextSet))
{

}



std::string
Expression::getText()
{
  return column.name + " " + operatorText + " " + valueText;
}



  }
}