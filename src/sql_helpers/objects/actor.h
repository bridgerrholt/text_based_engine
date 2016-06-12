#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_OBJECTS_ACTOR_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_OBJECTS_ACTOR_H

#include <common/string_ref.h>

#include "../object_core.h"

namespace tbe {
  namespace sql {

class Actor : public ObjectCore
{
  public:
    std::string getTableName() const { return "actors"; }

    class Data
    {
      public:
        std::string name;
        int         introId;
    };

    Actor(QueryDataCore queryData);

    std::vector<Data> run();

};



  }
}

#endif