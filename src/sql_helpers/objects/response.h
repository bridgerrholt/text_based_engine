#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_OBJECTS_RESPONSE_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_OBJECTS_RESPONSE_H

#include <common/string_ref.h>

#include "../object_core.h"

namespace tbe {
  namespace sql {

class Response : public ObjectCore
{
  public:
    std::string getTableName() const { return "responses"; }

    class Data
    {
      public:
        std::string textSpeak;
        int         nextId;
    };
    
    Response(QueryDataCore const & queryData);

    std::vector<Data> run();

};



  }
}

#endif