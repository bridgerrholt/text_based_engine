#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_GENERIC_ROW_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_GENERIC_ROW_H

#include <vector>

#include <com/string_ref.h>

#include "query.h"
#include "query_data.h"

namespace tbe {
  namespace sql {

class GenericQuery
{
  public:
    GenericQuery(
      QueryDataCore            const & queryData,
      std::vector<std::string> const & selectColumns,
      com::StringRef                   tableName);


    bool getColumn(com::StringRef columnName, int& id);

    virtual
    std::string getTableName() const = 0;


  protected:
    Query query_;


  private:
    std::string generateSelectClause() const;

    std::vector<std::string> selectColumns_;

};



  }
}

#endif