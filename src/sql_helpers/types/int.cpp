#include "int.h"

namespace tbe {
  namespace sql {
    namespace types {

Int::Int(DataType dataSet) :
  DynamicType(types::INT)
{
  data = dataSet;
}



    }
  }
}