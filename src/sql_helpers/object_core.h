/** @file object_core.h
    Declaration of the tbe::sql::ObjectCore class.

    @class tbe::sql::ObjectCore
    Parent of the SQL object classes.
*/

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_OBJECT_CORE_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_OBJECT_CORE_H

#include "query.h"
#include "query_data.h"

namespace tbe {
  namespace sql {

class QueryData;

class ObjectCore
{
  public:
    /// Primary constructor.
    /// @param[in] queryData All the information for the query.
    /// @param[in] tableName The name of the table for the query.
    ObjectCore(QueryDataFull const & queryData,
               com::StringRef        tableName);

    /// Returns the name of the object's table.
    /// @return The name of the query's table.
    virtual
    std::string getTableName() const = 0;

  protected:
    /// The constructed Query.
    Query query_;


};

  }
}

#endif