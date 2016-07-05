/** @file where_clause.h
    Declaration of the tbe::sql::SelectStatement class.

    @class tbe::sql::SelectStatement
    Fully describes an SQL SELECT statement.
*/

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_SELECT_STATEMENT_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_SELECT_STATEMENT_H

#include <memory>
#include <string>

#include "column_list.h"

namespace tbe {
  namespace sql {

class SelectStatementBase
{
  public:
    virtual
    std::string getText() = 0;
};


class SelectStatement
{
  public:
    std::string getText();

    ColumnList columnList;
};


class SelectStatementAll
{
  public:
    std::string getText();
};

  }
}

#endif