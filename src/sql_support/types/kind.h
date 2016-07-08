/// @file kind.h
/// Definition of the enum tbe::sql::types::Kind.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_KIND_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_TYPES_KIND_H

namespace tbe {
  namespace sql {
    namespace types {

/// Contains all the supported SQL types.
/// Starts at 1 to avoid being represented as false.
enum Kind
{
  INT = 1,
  TEXT
};

    }
  }
}

#endif