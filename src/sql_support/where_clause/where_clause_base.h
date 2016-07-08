/// @file where_clause_base.h
/// Declaration of the abstract base class tbe::sql::WhereClauseBase.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_WHERE_CLAUSE_BASE_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_WHERE_CLAUSE_BASE_H

#include <string>

namespace tbe {
  namespace sql {

/// An abstract class used as the base of structures that represent SQL WHERE clauses.
class WhereClauseBase
{
  public:
    /// Creates or gets the actual WHERE clause statement.
    /// Does not start with "WHERE".
    /// @return The body of the WHERE clause statement.
    virtual
    std::string getText() const = 0;

    /// Determines whether the object actually has any clause conditions or not.
    /// @return Whether the object has conditions or not.
    virtual
    bool hasConditions() const = 0;
};

  }
}

#endif