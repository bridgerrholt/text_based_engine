/// @file type_base.h
/// Declaration of the abstract base class tbe::dev_tools::types::TypeBase.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_BASE_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_BASE_H

#include "kind.h"

namespace tbe {
  namespace dev_tools {
    namespace types {

/// Base class for all the engine's specified types.
class TypeBase
{
  public:
    /// Primary constructor.
    /// @param kind Sets the underlying kind (@ref kind_).
    TypeBase(Kind kind);
    
    virtual
    ~TypeBase() = 0;

    /// Returns the underlying kind (@ref kind_).
    Kind getKind() const { return kind_; }


  private:
    /// Used for determining what type the object is.
    Kind kind_;
};


    }
  }
}

#endif