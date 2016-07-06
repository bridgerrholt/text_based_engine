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
  database_(database)
{
  tableName.swap(tableName_);
  swap(selectColumns, selectColumns_);
  whereClause.swap(whereClause_);

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

  return rawRun();
}



DynamicQuery::QueryResult
DynamicQuery::onlyRun()
{
  if (query_)
    rawRun();

  else {
    throw std::runtime_error(
      "Trying to execute a query which has not been compiled"
    );
  }
}



DynamicQuery::QueryResult
DynamicQuery::rawRun()
{
  using namespace types;

  query_->verifyColumnCount(selectColumns_.getColumns().size());
  QueryResult result;

  while (query_->nextRow()) {
    std::cerr << "nextRow\n";
    result.emplace_back(selectColumns_.getId());

    for (size_t i = 0; i < selectColumns_.getColumns().size(); ++i) {
      switch (selectColumns_.getColumns()[i]->kind) {
        case DynamicType::INT :
          result.back().varList.push_back(
            std::unique_ptr<DynamicType>(new Int(
              sqlite3_column_int(query_->getHandle(), i)
          )));
          break;

        case DynamicType::TEXT :
          result.back().varList.push_back(
            std::unique_ptr<DynamicType>(new Text(
              query_->readString(i)
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
  query_.reset(new Query(database_, generateQueryText()));
}



// Functions related to tableName_.
DynamicQuery&
DynamicQuery::setTableName(std::string & tableName)
{
  tableName.swap(tableName_);
  return *this;
}



// Functions related to selectColumns_.
DynamicQuery&
DynamicQuery::setSelectColumns(ColumnList & selectColumns)
{
  swap(selectColumns, selectColumns_);
  return *this;
}



// Functions related to whereClause_.
DynamicQuery&
DynamicQuery::setWhereClause(WhereClauseType whereClause)
{
  whereClause.swap(whereClause_);
  return *this;
}


  }
}