#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_OBJECT_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_OBJECT_H

#include "sql_object_core.h"

namespace tbe {
  namespace sql {

template <class T>
class Object : SqlObjectCore
{
  public:
    Object(SqlQueryData const & queryData);


    std::string getTableName() const;
    
    
  private:


};

  }
}

#endif