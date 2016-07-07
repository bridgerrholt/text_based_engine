#include "text.h"

namespace tbe {
  namespace sql {
    namespace types {

Text::Text(DataType const & dataSet) :
  DynamicType(types::TEXT)
{
  data = dataSet;
}



    }
  }
}