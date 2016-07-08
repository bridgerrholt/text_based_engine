#ifndef TEXT_BASED_ENGINE_SQL_SUPPORT_DYNAMIC_TYPE_H
#define TEXT_BASED_ENGINE_SQL_SUPPORT_DYNAMIC_TYPE_H

#include "types/kind.h"

namespace tbe {
  namespace sql {

class DynamicType
{
  public:
    DynamicType(types::Kind kind);
    
    virtual
    ~DynamicType() = 0;

    types::Kind getKind() const;


  private:
    types::Kind kind_;
};

  }
}

#endif