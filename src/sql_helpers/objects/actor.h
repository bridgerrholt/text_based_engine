#ifndef TEXT_BASED_ENGINE_SQL_HELPERS_OBJECTS_ACTOR_H
#define TEXT_BASED_ENGINE_SQL_HELPERS_OBJECTS_ACTOR_H

#include <com/string_ref.h>

#include "../object_core.h"
#include "../generic_query.h"

namespace tbe {
  namespace sql {

class Actor : public ObjectCore
{
  public:
    std::string getTableName() const { return "actors"; }

    class Data
    {
      public:
        std::string name;
        int         introId;
    };

    Actor(QueryDataCore queryData);

    std::vector<Data> run();

};



class ActorQuery : public GenericQuery
{
  public:
    std::string getTableName() const { return "actors"; }

    ActorQuery(
      QueryDataCore            const & queryData,
      std::vector<std::string> const & selectColumns);

    std::vector<Actor::Data> run();


  private:


};



  }
}

#endif