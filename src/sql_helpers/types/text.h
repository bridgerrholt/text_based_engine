#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_TYPES_TEXT_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_TYPES_TEXT_H

#include <string>

#include "../dynamic_type.h"

namespace tbe {
  namespace sql {
    namespace types {

class Text : public DynamicType
{
  public:
    typedef std::string DataType;

    Text(DataType const & dataSet);

    DataType data;
};

    }
  }
}

#endif