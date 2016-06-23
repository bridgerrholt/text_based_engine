#include "text.h"

namespace tbe {
  namespace sql {
    namespace types {

Text::Text(com::StringRef dataSet) :
  DynamicType(DynamicType::TEXT)
{
  data = dataSet;
}



    }
  }
}