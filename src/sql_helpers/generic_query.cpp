#include "generic_query.h"

namespace tbe {
  namespace sql {

GenericQuery::GenericQuery(
  QueryDataCore            const & queryData,
  std::vector<std::string> const & selectColumns,
  com::StringRef                   tableName) :

  selectColumns_(selectColumns),

  query_(QueryDataFull(queryData, generateSelectClause()), tableName)
{

}



std::string
GenericQuery::generateSelectClause() const
{
  std::string returnString = "";

  for (std::size_t i = 0; i < selectColumns_.size(); ++i) {
    returnString += selectColumns_[i];
    if (i < selectColumns_.size()-1)
      returnString += ", ";
  }

  return returnString;
}



bool
GenericQuery::getColumn(com::StringRef columnName, int& id)
{
  for (std::size_t i = 0; i < selectColumns_.size(); ++i) {
    if (columnName == selectColumns_[i]) {
      id = i;
      return true;
    }
  }

  return false;
}



  }
}