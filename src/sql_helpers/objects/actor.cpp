#include "actor.h"

#include <iostream>

namespace tbe {
  namespace sql {

Actor::Actor(QueryDataCore queryData) :
  ObjectCore(QueryDataFull(queryData, "name, intro_id"), getTableName())
{
  std::cerr << "Actor made\n";
}



std::vector<Actor::Data>
Actor::run()
{
  query_.verifyColumnCount(2);
  std::vector<Data> outList;

  while (query_.nextRow()) {
    outList.push_back(Data{
      query_.readString(0),
      sqlite3_column_int(query_.getHandle(),  1)
    });
  }

  return outList;
}



ActorQuery::ActorQuery(QueryDataCore            const & queryData,
                       std::vector<std::string> const & selectColumns) :
  GenericQuery(queryData, selectColumns, getTableName())
{

}



std::vector<Actor::Data>
ActorQuery::run()
{
  query_.verifyColumnCount(2);
  std::vector<Actor::Data> outList;

  while (query_.nextRow()) {
    Actor::Data actor;
    int columnId;
    if (getColumn("name", columnId))
      actor.name = query_.readString(columnId);
    if (getColumn("intro_id", columnId))
      actor.introId = sqlite3_column_int(query_.getHandle(),  columnId);
  }

  return outList;
}



  }
}