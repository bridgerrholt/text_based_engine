#include "int.h"

namespace tbe {
  namespace sql {
    namespace types {

Int::Int(int dataSet) :
  DynamicType(DynamicType::INT)
{
  data = dataSet;
}



    }
  }
}