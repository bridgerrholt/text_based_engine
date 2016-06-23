#include "option.h"

namespace tbe {
  namespace sql {

Option::Option(QueryDataCore const & queryData) :
  ObjectCore(QueryDataFull(queryData, "character_id, option_list_id,"
                                      "text_display, text_speak, next_id"),
             getTableName())
{

}



std::vector<Option::Data>
Option::run()
{
  query_.verifyColumnCount(5);
  std::vector<Data> outList;

  while (query_.nextRow()) {
    outList.push_back(Data{
      sqlite3_column_int(query_.getHandle(),  0),
      sqlite3_column_int(query_.getHandle(),  1),
      query_.readString(2),
      query_.readString(3),
      sqlite3_column_int(query_.getHandle(),  4)
    });
  }

  return outList;
}



  }
}