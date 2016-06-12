#ifndef TEXT_BASED_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_H

#include <vector>
#include <map>
#include <memory>

#include <common/string_ref.h>

#include <sqlite3.h>

#include "sql_helpers/query.h"

#include "sql_helpers/objects/include.h"

namespace tbe {

class Engine
{
  public:
    Engine();
    ~Engine();

    void loadDatabase(com::StringRef fileName);

    void run();

  private:
    void openDatabase(com::StringRef fileName);
    void closeDatabase();

    static std::size_t askQuestion(
      std::vector<std::string> const & responseOptions,
      int startNum = 1);

    static std::size_t askQuestion(
      std::vector<std::string> const & responseOptions,
      com::StringRef question,
      int startNum = 1);


    enum QueryKind
    {
      GET_ACTORS
    };

    void prepareSqlQueries();
    void prepareSingleSqlQuery(QueryKind query, com::StringRef queryText);

    static int actorCallback(void* engineRef, int argc,
      char** argv, char** columnNames);

    void getActors();
    std::vector<sql::Option::Data> getOptionList(com::StringRef conditions);

    sql::Response::Data getResponse(int id);

    bool databaseOpenCalled_;
    bool databaseOpened_;
    sqlite3* database_;

    std::map<QueryKind, std::unique_ptr<sql::Query> > sqlQueries_;
    std::vector<sql::Actor::Data> actors_;

};

}

#endif