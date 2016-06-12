#include "response.h"

namespace tbe {
  namespace sql {

Response::Response(QueryDataCore const & queryData) :
  ObjectCore(QueryDataFull(queryData, "text_speak, next_id"), getTableName())
{

}



std::vector<Response::Data>
Response::run()
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