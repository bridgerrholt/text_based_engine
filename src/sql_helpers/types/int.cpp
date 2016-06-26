#include "int.h"

namespace tbe {
  namespace sql {
    namespace types {

Int::Int(DataType dataSet) :
  DynamicType(DynamicType::INT)
{
  data = dataSet;
}



    }
  }
}