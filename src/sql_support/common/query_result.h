/// @file query_result.h
/// Declares the typedef tbe::sql::QueryResult.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_COMMON_QUERY_RESULT_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_COMMON_QUERY_RESULT_H

#include <vector>

#include "../query_object.h"

namespace tbe {
  namespace sql {

typedef std::vector<QueryObject> QueryResult;

  }
}

#endif