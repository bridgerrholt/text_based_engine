#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_TYPES_INT_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_TYPES_INT_H

#include "../dynamic_type.h"

namespace tbe {
  namespace sql {
    namespace types {

class Int : public DynamicType
{
  public:
    Int(int dataSet);

    int data;

  private:
  
};

    }
  }
}

#endif