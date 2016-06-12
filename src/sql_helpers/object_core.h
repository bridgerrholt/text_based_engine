#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_OBJECT_CORE_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_OBJECT_CORE_H

#include "query.h"
#include "query_data.h"

namespace tbe {
  namespace sql {

class QueryData;

class ObjectCore
{
  public:
    ObjectCore(QueryDataFull const & queryData, com::StringRef tableName);


    virtual
    std::string getTableName() const = 0;
    
    
  protected:
    Query query_;


};

  }
}

#endif