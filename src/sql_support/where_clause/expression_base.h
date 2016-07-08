/// @file expression_base.h
/// Declaration of the abstract base class tbe::sql::ExpressionBase.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_EXPRESSION_BASE_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_EXPRESSION_BASE_H

#include <string>

namespace tbe {
  namespace sql {

/// An abstract class used as the base of structures that represent SQL WHERE clause expressions.
class ExpressionBase
{
  public:
    /// Creates or gets the actual WHERE clause expression text.
    /// @return The WHERE clause expression text.
    virtual
    std::string getText() = 0;
};

  }
}

#endif