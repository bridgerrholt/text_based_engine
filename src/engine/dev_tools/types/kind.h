/// @file kind.h
/// Definition of the enum tbe::sql::types::Kind.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_KIND_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPES_KIND_H

namespace tbe {
  namespace dev_tools {
    namespace types {

/// Contains all the supported SQL types.
/// Starts at 1 to avoid being represented as false.
enum Kind
{
  BOOL = 1,
  INT,
  TEXT
};

    }
  }
}

#endif