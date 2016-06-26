#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_DATABASE_STRUCTURE_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_DATABASE_STRUCTURE_H

#include <string>

#include "dynamic_type.h"
#include "column_info.h"

namespace tbe {
  namespace sql {

using namespace column_info_types;

class Tables
{
  public:
    class Actors
    {
      public:
        Int  id      = { "id"       };
        Text name    = { "name"     };
        Int  introId = { "intro_id" };
    } actors;

  private:
};



  }
}

#endif