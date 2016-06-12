#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_SELECT_CLAUSE_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_SELECT_CLAUSE_H

#include <vector>

#include <common/string_ref.h>

namespace tbe {
  namespace sql {

class SelectClause
{
  public:
    SelectClause(bool selectAllColumns);
    SelectClause(std::vector<std::string> const & columnList);

  private:

};

  }
}

#endif