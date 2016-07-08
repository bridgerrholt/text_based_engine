/// @file column_info.h
/// Declaration of the class tbe::sql::ColumnInfo.
/// Also defines the class template inherited from tbe::sql::ColumnInfo,
/// tbe::sql::ColumnInfoSpecific.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_COLUMN_INFO_COLUMN_INFO_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_COLUMN_INFO_COLUMN_INFO_H

#include <string>
#include <unordered_map>

#include "../column_list_id.h"

#include "../types/kind.h"

namespace tbe {
  namespace sql {
    
/// Contains information about a specific column within an undescribed table.
class ColumnInfo
{
  public:
    /// Primary constructor.
    /// @param[in] nameSet Moves into @ref name.
    /// @param[in] kindSet Copies into @ref kind.
    ColumnInfo(std::string nameSet,
               types::Kind kindSet);

    /// Returns an id from @ref idMap_ based on the key @p columnListId.
    /// Throws an exception if @p columnListId is not a key within @ref idMap_.
    ///
    /// @param[in] columnListId The key to find in @ref idMap_.
    /// @return The value assosiated with the key.
    std::size_t getId(std::size_t columnListId) const;

    /// Associates the value of @p columnListId with @p id within @ref idMap_.
    /// Throws an exception if the value of @p columnListId is already a key within @ref idMap_.
    ///
    /// @param[in] columnListId The id of the query, is made a key within idMap_.
    /// @param[in] id           The index of this column within the query,
    ///                         is made a value associated with @p columnListId.
    void insertId(ColumnListId columnListId,
                  std::size_t  id);

    /// The name of the column within the database.
    std::string name;

    /// The type that the column should be interpretted as.
    types::Kind kind;


  private:
    /// Maps the ids of ColumnList objects to indexes of columns within SQL queries.
    std::unordered_map<std::size_t, std::size_t> idMap_;

};



  }
}

#endif