/// @file basic_column_info.h
/// Definition of the derived class template tbe::sql::BasicColumnInfo.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_COLUMN_INFO_BASIC_COLUMN_INFO_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_COLUMN_INFO_BASIC_COLUMN_INFO_H

#include "column_info.h"

namespace tbe {
  namespace sql {

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