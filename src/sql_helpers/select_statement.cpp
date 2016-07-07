#include "select_statement.h"

#include "column_info.h"

namespace tbe {
  namespace sql {

std::string
SelectStatement::getText()
{
  auto columns = columnList.getColumns();

  if (columns.size() == 0)
    return "";

  std::string toReturn;

  for (std::size_t i = 0; i < columns.size()-1; ++i) {
    toReturn += columns[i]->name + ", ";
  }

  return toReturn + columns.back()->name;
}


std::string
SelectStatementAll::getText()
{
  return "*";
}

  }
}