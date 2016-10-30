/// @file basic_type.h
/// Definition of the class template tbe::sql::types::BasicType.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_BASIC_TYPE_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_COMMON_BASIC_TYPE_H

#include <string>

#include "../type_base.h"

#include "../kind.h"

namespace tbe {
  namespace dev_tools {
    namespace types {
      namespace support {
      
template <class T>
constexpr Kind matchUp();

template <>
constexpr Kind matchUp<bool>() { return BOOL; }

template <>
constexpr Kind matchUp<int>() { return INT; }

template <>
constexpr Kind matchUp<std::string>() { return TEXT; }

      }



/// Class template to be used for all the supported SQL types.
/// @tparam T The underlying type to use for representing the SQL type.
/// @tparam k The name (within the enum Kind) for identification.
template <class T, Kind k = support::matchUp<T>()>
class BasicType : public TypeBase
{
  public:
    /// Allows usage of the type elsewhere.
    typedef T DataType;

    /// Primary constructor.
    /// @param[in] dataSet Moves into @ref data.
    BasicType(DataType dataSet) : TypeBase(k)
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