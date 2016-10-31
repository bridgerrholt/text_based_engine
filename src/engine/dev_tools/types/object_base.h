/// @file type_base.h
/// Declaration of the abstract base class tbe::dev_tools::types::ObjectBase.

#ifndef TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_BASE_H
#define TEXT_BASED_ENGINE_ENGINE_DEV_TOOLS_TYPE_BASE_H

#include "type_id.h"

namespace tbe {
  namespace dev_tools {
    namespace types {

/// Base class for all the engine's objects.
class ObjectBase
{
  public:
    /// Primary constructor.
    /// @param kind Sets the underlying kind (@ref kind_).
    ObjectBase(TypeId typeId);
    
    virtual
    ~ObjectBase() = 0;

    /// Returns the id of the type (@ref kind_).
    TypeId getTypeId() const { return typeId_; }


  private:
    /// Used for determining what type the object is.
    TypeId typeId_;
};


    }
  }
}

#endif