#include "mapped_query.h"

#include <iostream>

#include "types/include.h"

namespace tbe {
  namespace sql {

MappedQuery::MappedQuery(
  QueryDataCore const & queryData,
  std::string   const & tableName,
  ColumnList          & selectColumns) :

  selectColumns_(std::move(selectColumns)),

  query_(QueryDataFull(queryData, generateSelectClause()), tableName)
{

}



MappedQuery::QueryResult
MappedQuery::run()
{
  using namespace types;

  query_.verifyColumnCount(selectColumns_.getColumns().size());
  QueryResult result;


  while (query_.nextRow()) {
    std::cerr << "nextRow\n";
    result.emplace_back(selectColumns_.getId());

    for (size_t i = 0; i < selectColumns_.getColumns().size(); ++i) {
      switch (selectColumns_.getColumns()[i]->kind) {
        case DynamicType::INT :
          result.back().varList.push_back(
            std::unique_ptr<DynamicType>(new Int(
              sqlite3_column_int(query_.getHandle(), i)
          )));
          break;

        case DynamicType::TEXT :
          result.back().varList.push_back(
            std::unique_ptr<DynamicType>(new Text(
              query_.readString(i)
          )));
          break;

        default :
          throw std::runtime_error("Invalid DynamicType::Kind");
      }
    }
  }

  return result;
}



std::string
MappedQuery::generateSelectClause() const
{
  std::string returnString = "";

  std::cerr << "Generating\n";

  for (size_t i = 0; i < selectColumns_.getColumns().size(); ++i) {
    returnString += selectColumns_.getColumns().at(i)->name;
    if (i < selectColumns_.getColumns().size() - 1)
      returnString += ", ";
  }

  return returnString;
}




MappedQuery::QueryObject::QueryObject(size_t columnListId) :
  columnListId_(columnListId)
{

}

  }
}