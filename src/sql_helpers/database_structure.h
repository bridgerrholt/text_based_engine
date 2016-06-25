#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_DATABASE_STRUCTURE_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_DATABASE_STRUCTURE_H

#include <string>

#include "dynamic_type.h"
#include "column_info.h"

namespace tbe {
  namespace sql {

class Tables
{
  public:
    class Actors
    {
      public:
        ColumnInfo
          id      = { "id",       DynamicType::INT  },
          name    = { "name",     DynamicType::TEXT },
          introId = { "intro_id", DynamicType::INT  };
    } actors;

  private:
};



  }
}

#endif