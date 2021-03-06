/// @file database_structure.h
/// Declaration of the class tbe::sql::Tables.

#ifndef TEXT_BASED_ENGINE_DATABASE_STRUCTURE_H
#define TEXT_BASED_ENGINE_DATABASE_STRUCTURE_H

#include <string>

#include "sql_support/dynamic_type.h"
#include "sql_support/column_info/basic_column_info.h"

namespace tbe {
  namespace sql {

/// Simply contains tbe::sql::BasicColumnInfo objects, forming the structure of the database used
/// in this project.
class Tables
{
  public:
    class Actors
    {
      public:
        types::col::Int  id      = { "id"       };
        types::col::Text name    = { "name"     };
        types::col::Int  introId = { "intro_id" };
    } actors;


    class Options
    {
      public:
        types::col::Int  id           = { "id"             };
        types::col::Int  characterId  = { "character_id"   };
        types::col::Int  optionListId = { "option_list_id" };
        types::col::Text textDisplay  = { "text_display"   };
        types::col::Text textSpeak    = { "text_speak"     };
        types::col::Int  nextId       = { "next_id"        };
    } options;


    class Responses
    {
      public:
        types::col::Int  id        = { "id"         };
        types::col::Text textSpeak = { "text_speak" };
        types::col::Int  nextId    = { "next_id"    };
    } responses;
};

  }
}

#endif