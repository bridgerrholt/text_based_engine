/// @file expression.h
/// Declaration of the inherited class tbe::sql::Expression.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_EXPRESSION_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_WHERE_CLAUSE_EXPRESSION_H

#include <string>

#include "expression_base.h"

#include "../column_info/column_info.h"

namespace tbe {
  namespace sql {

/// Fully describes an SQL WHERE clause expression by containing the necessary values.
class Expression : public ExpressionBase
{
  public:
    /// Primary constructor.
    /// @param[in] columnSet       Copied into @ref column.
    /// @param[in] operatorTextSet Moved into @ref operatorText.
    /// @param[in] valueTextSet    Moved into @ref valueText.
    Expression(ColumnInfo const & columnSet,
               std::string        operatorTextSet,
               std::string        valueTextSet);

    /// Constant reference to a column representing which column in the table to test.
    ColumnInfo const & column;
    /// The text used to represent a specific operator.
    std::string        operatorText;
    /// The value being tested against.
    std::string        valueText;

    /// Concatenates all the values together.
    /// "%columnName% %operatorText% %valueText%"
    std::string getText();
};

  }
}

#endif