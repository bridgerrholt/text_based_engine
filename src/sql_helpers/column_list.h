/** @file column_list.h
    Declaration of the tbe::sql::ColumnList class.

    @class tbe::sql::ColumnList
    Manages a list of pointers to ColumnInfo objects.
*/

#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_LIST_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_COLUMN_LIST_H

#include <vector>

#include "column_list_id.h"

#include "column_info.h"

namespace tbe {
  namespace sql {

class ColumnList
{
  public:
    /// The underlying list of ColumnInfo objects.
    typedef std::vector<ColumnInfo*> ColumnInfoList;

    friend void swap(ColumnList& first, ColumnList& second);

    /** Primary constructor, generates a unique id.
        No mechanism tracks ColumnList objects, so an exception will be thrown if
        too many are created in total (the maximum number depends on the architecture but
        is most likely extremely high).
    */
    ColumnList();

    /// Creates @ref columns_ from @p columns and generates a unique id.
    /// @param columns Gets swapped with @ref columns_.
    ColumnList(ColumnInfoList& columns);

    /// @param columns Gets copied to @ref columns_.
    ColumnList(ColumnInfoList const & columns);

    /// Copying is disallowed because of the unqiue id system.
    ColumnList(ColumnList const & other) = delete;

    /// Move operator.
    ColumnList(ColumnList&& other);

    ~ColumnList();

    /** Pushes a reference to the specified column and gives it this object's unique id.
        An exception will be thrown if the column's internal map already
        contains this object's unique id.

        @param column The column to be modified and copied.
    */
    void push(ColumnInfo& column);

    void push(std::initializer_list<ColumnInfo*> columns);

    /// Lists the text within the items comma-separated and in order. 
    std::string getText();

    /// Returns the underlying ColumnInfoList.
    ColumnInfoList const & getColumns() const { return columns_; }

    /// Returns the unique id.
    ColumnListIdSizeType   getId()      const { return id_.get(); }


  private:
    /// Constructs with a passed id.
    ColumnList(ColumnListId id);

    /// The underlying ColumnInfoList.
    /// Will only ever be expanded, never shrunk.
    ColumnInfoList columns_;

    // The unique id given to each ColumnList object.
    ColumnListId id_;
};



  }
}

#endif