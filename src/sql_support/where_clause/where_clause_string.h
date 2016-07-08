/// @file where_clause_string.h
/// Declaration of the inherited class tbe::sql::WhereClauseString.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_WHERE_CLAUSE_STRING_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_WHERE_CLAUSE_STRING_H

#include <string>

#include "where_clause_base.h"

namespace tbe {
  namespace sql {

/// Fully describes an SQL WHERE clause by containing the body of the statement.
class WhereClauseString : public WhereClauseBase
{
  public:
    /// Primary constructor.
    /// @param[in] textSet Moved into @ref text.
    WhereClauseString(std::string textSet);

    /// Simply returns the actual statement (@ref text).
    std::string getText()        const;

    /// Returns whether the statement is empty or not.
    bool        hasConditions()  const;

    /// The statement.
    std::string text;
};

  }
}

#endif