#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_TYPES_TEXT_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_TYPES_TEXT_H

#include "../dynamic_type.h"

#include <com/string_ref.h>

namespace tbe {
  namespace sql {
    namespace types {

class Text : public DynamicType
{
  public:
    Text(com::StringRef dataSet);

    std::string data;

  private:
  
};

    }
  }
}

#endif