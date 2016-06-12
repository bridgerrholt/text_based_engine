#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_OBJECTS_OPTION_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_OBJECTS_OPTION_H

#include <common/string_ref.h>

#include "../object_core.h"

namespace tbe {
  namespace sql {

class Option : public ObjectCore
{
  public:
    std::string getTableName() const { return "options"; }

    class Data
    {
      public:
        int         characterId;
        int         optionListId;
        std::string textDisplay;
        std::string textSpeak;
        int         nextId;
    };

    Option(QueryDataCore const & queryData);

    std::vector<Data> run();
};



  }
}

#endif