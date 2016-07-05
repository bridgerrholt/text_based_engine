#include "dynamic_query.h"

#include <iostream>

namespace tbe {
  namespace sql {

std::string
DynamicQuery::swapGen(std::string     & tableName,
                      ColumnList      & selectColumns,
                      WhereClauseType & whereClause)
{
  tableName.swap(tableName_);
  swap(selectColumns, selectColumns_);
  whereClause.swap(whereClause_);

  return generateQueryText();
}



DynamicQuery::DynamicQuery(sqlite3       *  database,
                           std::string   && tableName,
                           ColumnList    &  selectColumns,
                           WhereClauseType  whereClause) :
  database_(database),

  query_(database_,
         swapGen(tableName,
                 selectColumns,
                 whereClause
  )),

  mustCompile_(false)
{
  std::cerr << "DynamicQuery :\n"
    " db " << database_ << "\n"
    " tn " << tableName_ << "\n"
    " id " << selectColumns_.getId() << '\n';
}



std::string
DynamicQuery::generateQueryText()
{
  std::string toReturn = "SELECT " + selectColumns_.getText() +
                        " FROM "   + tableName_;

  if (whereClause_->hasConditions())
    toReturn +=         " WHERE "  + whereClause_->getText();

  toReturn += ';';
  return toReturn;
}



DynamicQuery::QueryResult
DynamicQuery::run()
{
  compile();

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



void
DynamicQuery::compile()
{
  if (mustCompile_) rawCompile();
}



void
DynamicQuery::rawCompile()
{
  query_ = Query(database_, generateQueryText());
  mustCompile_ = false;
}



void
DynamicQuery::setTableName(std::string & tableName)
{
  tableName.swap(tableName_);
  rawCompile();
}



  }
}