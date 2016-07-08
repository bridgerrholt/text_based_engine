/// @file where_clause.h
/// Declaration of the inherited class tbe::sql::WhereClause.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_WHERE_CLAUSE_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_WHERE_CLAUSE_H

#include <memory>
#include <string>
#include <vector>

#include "where_clause_base.h"

namespace tbe {
  namespace sql {

class ExpressionBase;

/// Fully describes an SQL WHERE clause by containing all the expressions and conjunctions.
class WhereClause : public WhereClauseBase
{
  public:
    /// The type used to represent each expression.
    typedef std::unique_ptr<ExpressionBase> ExpressionType;
    /// The type used to represent each conjunction.
    typedef std::string                     ConjunctionType;

    WhereClause() = default;

    /// Constructs with a single first element.
    WhereClause(ExpressionType firstExpression);
    
    /// Attempts to push the expression.
    /// Throws an error if called when a conjunction was needed as well.
    /// @param[in] expression The expression to be pushed.
    void push(ExpressionType expression);

    /// Attempts to push both the conjunction and the expression.
    /// Throws an error if there has been no expressions so far,
    /// meaning the conjunction is not needed.
    ///
    /// @param[in] conjunction Moved in to the underlying list.
    /// @param[in] expression  Moved in to the underlying list.
    void push(ConjunctionType conjunction,
              ExpressionType  expression);

    /// Lists out each expression with each conjunction in between.
    /// "%expression0% %conjunction0% " ... "%expressionLast%"
    std::string getText()       const;

    /// Returns whether there are any expressions or not.
    bool        hasConditions() const;
    
    /// Returns a modifiable reference to the specific expression.
    ExpressionBase& getExpression(std::size_t index)
      { return *expressions_.at(index); }

    /// Returns a modifiable reference to the specific conjunction.
    ConjunctionType& getConjunction(std::size_t index)
      { return conjunctions_.at(index); }


  private:
    /// Pushes the expression without checking that a conjunction is needed.
    void rawPush(ExpressionType expression);


    /// The list of expressions. May be of any size.
    std::vector<ExpressionType>  expressions_;

    /// The list of conjunctions.
    /// Guaranteed to be of size 0 if expressions_ is,
    /// or else 1 less than the size of expressions_.
    std::vector<ConjunctionType> conjunctions_;
};

  }
}

#endif