/// @file kind.h
/// Definition of the enum tbe::sql::types::TypeId.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_KIND_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_KIND_H

#include <string>

namespace tbe {
  namespace dev_tools {
    namespace types {

/// Contains every supported type.
/// Starts at 1 to avoid being represented as false.
enum TypeId
{
  BOOL = 1,
  INT,
  TEXT
};



template <class T>
constexpr TypeId matchUp();

template <>
constexpr TypeId matchUp<bool>() { return BOOL; }

template <>
constexpr TypeId matchUp<int>() { return INT; }

template <>
constexpr TypeId matchUp<std::string>() { return TEXT; }

    }
  }
}

#endif