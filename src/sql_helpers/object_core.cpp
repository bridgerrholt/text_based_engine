/// @file object_core.cpp
/// Definition of the tbe::sql::ObjectCore class.

#include "object_core.h"

namespace tbe {
  namespace sql {

ObjectCore::ObjectCore(QueryDataFull const & queryData,
                       com::StringRef        tableName) :

  query_(queryData, tableName)
{
  
}



  }
}