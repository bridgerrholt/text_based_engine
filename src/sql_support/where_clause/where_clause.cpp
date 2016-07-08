/// @file where_clause.cpp
/// Definition of the inherited class tbe::sql::WhereClause

#include "where_clause.h"

#include <utility> // std::move

#include "expression_base.h"

namespace tbe {
  namespace sql {

WhereClause::WhereClause(ExpressionType firstExpression)
{
  rawPush(std::move(firstExpression));
}



void
WhereClause::push(ExpressionType expression)
{
  // This function should only be called if no expression has been pushed yet.
  if (expressions_.size() >= 1) {
    throw std::runtime_error(
      "Cannot push an expression without a conjunction"
    );
  }

  rawPush(std::move(expression));
}


void
WhereClause::push(ConjunctionType conjunction,
                  ExpressionType  expression)
{
  if (expressions_.size() == 0) {
    throw std::runtime_error(
      "Cannot push a conjunction without first having an expression"
    );
  }

  conjunctions_.emplace_back(std::move(conjunction));
  rawPush(std::move(expression));
}



void
WhereClause::rawPush(ExpressionType expression)
{
  expressions_.push_back(std::move(expression));
}



std::string
WhereClause::getText() const
{
  // Empty clause, no expressions or conjunctions.
  if (expressions_.size() == 0)
    return "";

  // Only 1 expression, no conjunctions.
  else if (expressions_.size() == 1)
    return expressions_[0]->getText();

  // Multiple expressions, at least 1 conjunction.
  else {
    std::string toReturn;

    // There should be 1 less conjunction than there are expressions.
    for (std::size_t i = 0; i < conjunctions_.size(); ++i) {
      // Add the expression with padding for the conjunction.
      toReturn += expressions_[i]->getText() + " " +
      // Add the conjunction with padding for the next expression.
                  conjunctions_[i] + " ";
    }

    // Add the final expression.
    return toReturn + expressions_.back()->getText();
  }
}



bool
WhereClause::hasConditions() const
{
  return (expressions_.size() > 0);
}



  }
}