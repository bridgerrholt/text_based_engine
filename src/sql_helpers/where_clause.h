/** @file where_clause.h
    Declaration of the tbe::sql::WhereClause class.

    @class tbe::sql::WhereClause
    Fully describes an SQL WHERE clause.
*/

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_WHERE_CLAUSE_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_WHERE_CLAUSE_H

#include <memory>
#include <string>
#include <vector>

#include "column_info.h"

namespace tbe {
  namespace sql {

class ExpressionBase
{
  public:
    virtual
    std::string getText() = 0;

  private:


};


class Expression : public ExpressionBase
{
  public:
    Expression(ColumnInfo  const & columnSet,
               std::string const & operatorTextSet,
               std::string const & valueTextSet);

    ColumnInfo const & column;
    std::string        operatorText;
    std::string        valueText;

    std::string getText();
};


class ExpressionString : public ExpressionBase
{
  public:
    std::string text;

    std::string getText();
};



class WhereClauseBase
{
  public:
    virtual
    std::string getText() const = 0;

    virtual
    bool hasConditions() const = 0;
};


class WhereClause : public WhereClauseBase
{
  public:
    typedef std::unique_ptr<ExpressionBase> ExpressionType;
    typedef std::string                     ConjunctionType;

    WhereClause();
    WhereClause(ExpressionType firstExpression);
    
    /// Attempts to push the expression.
    /// Throws an error if called when a conjunction was needed as well.
    /// @param expression[in] The expression to be pushed.
    void push(ExpressionType expression);

    /** Attempts to push both the conjunction and the expression.
        Throws an error if there has been no expressions so far,
        meaning the conjunction is not needed.

        @param[in] conjunction The conjunction to be pushed.
        @param[in] expression  The expression to be pushed.
    */
    void push(ConjunctionType const & conjunction,
              ExpressionType          expression);

    std::string getText()       const;
    bool        hasConditions() const;
    
    ExpressionBase& getExpression(size_t index)
      { return *expressions_.at(index); }

    ConjunctionType& getConjunction(size_t index)
      { return conjunctions_.at(index); }

  private:
    /// Pushes the expression without checking that a conjunction is needed.
    void rawPush(ExpressionType expression);

    std::vector<ExpressionType>  expressions_;
    std::vector<ConjunctionType> conjunctions_;

};


class WhereClauseString : public WhereClauseBase
{
  public:
    std::string getText()        const;
    bool        hasConditions()  const;

    std::string text;
};

  }
}

#endif