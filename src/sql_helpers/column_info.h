/// @file column_info.h
/// Declaration of the tbe::sql::ColumnInfo class.

/// @class tbe::sql::ColumnInfo
/// Contains information about a specific column within an undescribed table.

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_INFO_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_INFO_H

#include <string>
#include <unordered_map>

#include "column_list_id.h"

#include "types/kind.h"

namespace tbe {
  namespace sql {

class ColumnInfo
{
  public:
    /// Primary constructor.
    /// @param nameSet Sets @ref name.
    /// @param kindSet Sets @ref kind.
    ColumnInfo(std::string const & nameSet,
               types::Kind         kindSet);

    /// Returns an id from @ref idMap_ based on the key @p columnListId.
    /// Throws an exception if @p columnListId is not a key within @ref idMap_.
    ///
    /// @param columnListId The key to find in @ref idMap_.
    /// @return The value assosiated with the key.
    size_t getId(size_t columnListId) const;

    /// Associates the value of @p columnListId with @p id within @ref idMap_.
    /// Throws an exception if the value of @p columnListId is already a key within @ref idMap_.
    ///
    /// @param columnListId The id of the query, is made a key within idMap_.
    /// @param id           The index of this column within the query,
    ///                     is made a value associated with @p columnListId.
    void insertId(ColumnListId columnListId,
                  size_t       id);

    /// The name of the column within the database.
    std::string name;

    /// The type that the column should be read as.
    types::Kind kind;


  private:
    /// Maps the ids of ColumnList objects to indexes of columns within SQL queries.
    std::unordered_map<size_t, size_t> idMap_;

};



/// Basic template for ColumnInfo objects.
/// The main purpose of this template is to allow function overloading based on the type of the
/// specific column, making the user not have to type as many repetitive casts.
/// @param K Used to express that specific instansiation's type.
template <types::Kind K>
class ColumnInfoSpecific : public ColumnInfo
{
  public:
    /// Primary constructor.
    /// Simply calls the primary ColumnInfo constructor with a passed name and the type @ref K.
    /// @param[in] nameSet Passed as the column name to the ColumnInfo constructor.
    ColumnInfoSpecific(std::string const & nameSet) :
      ColumnInfo(nameSet, K)
    {
    
    }
};



      namespace types {

        /// Provides shortcuts for instantiations of ColumnInfoSpecific.
        namespace col {

typedef ColumnInfoSpecific<types::INT>  Int;
typedef ColumnInfoSpecific<types::TEXT> Text;

      }
    }

  } // sql
} // tbe

#endif