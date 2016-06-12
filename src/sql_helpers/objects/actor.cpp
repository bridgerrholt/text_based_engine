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
  std::vector<Data> outList;

  while (query_.nextRow()) {
    outList.push_back(Data{
      query_.readString(0),
      sqlite3_column_int(query_.getHandle(),  1)
    });
  }

  return outList;
}



  }
}