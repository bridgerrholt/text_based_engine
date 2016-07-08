/// @file where_clause.h
/// Declaration of the inherited class tbe::sql::ExpressionString.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_EXPRESSION_STRING_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_EXPRESSION_STRING_H

#include <string>

#include "expression_base.h"

namespace tbe {
  namespace sql {

/// Fully describes an SQL WHERE clause by expression containing the text of the statement.
class ExpressionString : public ExpressionBase
{
  public:
    /// Primary constructor.
    /// @param[in] textSet Moved into @ref text.
    ExpressionString(std::string textSet);
    
    /// Simply returns the actual statement (@ref text).
    std::string getText();

    /// The full statement.
    std::string text;

};

  }
}

#endif