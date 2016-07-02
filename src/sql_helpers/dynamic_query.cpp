#include "dynamic_query.h"

namespace tbe {
  namespace sql {

DynamicQuery::DynamicQuery(Data       & data,
                           ColumnList & selectColumns)
{
  std::swap(data,          data_);
       swap(selectColumns, selectColumns_);
}



  }
}