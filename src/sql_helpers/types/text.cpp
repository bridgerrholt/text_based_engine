#include "text.h"

namespace tbe {
  namespace sql {
    namespace types {

Text::Text(DataType const & dataSet) :
  DynamicType(DynamicType::TEXT)
{
  data = dataSet;
}



    }
  }
}