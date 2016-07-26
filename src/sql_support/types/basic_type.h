/// @file basic_type.h
/// Definition of the class template tbe::sql::types::BasicType.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_BASIC_TYPE_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_BASIC_TYPE_H

#include <string>

#include "../dynamic_type.h"

#include "kind.h"

namespace tbe {
  namespace sql {
    namespace types {

/// Class template to be used for all the supported SQL types.
/// @tparam T The underlying type to use for representing the SQL type.
/// @tparam k The name (within the enum Kind) for identification.
template <class T, Kind k>
class BasicType : public DynamicType
{
  public:
    /// Allows usage of the type elsewhere.
    typedef T DataType;

    /// Primary constructor.
    /// @param[in] dataSet Moves into @ref data.
    BasicType(DataType dataSet) : DynamicType(k)
    {
      data = std::move(dataSet);
    }

    /// The underlying data.
    DataType data;
};

    }
  }
}

#endif