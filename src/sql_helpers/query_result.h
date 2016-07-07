#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_RESULT_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_QUERY_RESULT_H

#include <vector>

#include "query_object.h"

namespace tbe {
  namespace sql {

typedef std::vector<QueryObject> QueryResult;

  }
}

#endif