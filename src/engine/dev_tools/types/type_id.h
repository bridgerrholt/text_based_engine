/// @file type_id.h
/// Definition of the enum tbe::sql::types::TypeId.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_KIND_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_KIND_H

#include <string>

namespace tbe {
  namespace dev_tools {
    namespace types {

/// Expresses a certain engine type.
enum class TypeId
{
  BOOL,
  INT,
  STRING
};


template <class T>
static constexpr TypeId matchToTypeId();


template <>
constexpr TypeId
matchToTypeId<bool>() { return TypeId::BOOL; }

template <>
constexpr TypeId
matchToTypeId<int>() { return TypeId::INT; }

template <>
constexpr TypeId
matchToTypeId<std::string>() { return TypeId::STRING; }


    }
  }
}

#endif