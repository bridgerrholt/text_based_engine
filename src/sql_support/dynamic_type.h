/// @file dynamic_type.h
/// Declaration of the abstract base class tbe::sql::DynamicType.

#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_DYNAMIC_TYPE_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_DYNAMIC_TYPE_H

#include "types/kind.h"

namespace tbe {
  namespace sql {

/// Used for representing SQL types.
class DynamicType
{
  public:
    /// Primary constructor.
    /// @param kind Sets the underlying kind (@ref kind_).
    DynamicType(types::Kind kind);
    
    /// Makes the class abstract.
    virtual
    ~DynamicType() = 0;

    /// Returns the underlying kind (@ ref kind_).
    types::Kind getKind() const { return kind_; }


  private:
    /// Used for determining what kind of SQL variable it represents.
    types::Kind kind_;
};

  }
}

#endif