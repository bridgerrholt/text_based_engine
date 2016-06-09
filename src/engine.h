#ifndef TEXT_BASED_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_H

#include <vector>
#include <map>
#include <memory>

#include <common/string_ref.h>

#include <sqlite3.h>

#include "sql_query.h"
#include "actor.h"
#include "option.h"
#include "response.h"

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


    enum Query
    {
      GET_ACTORS
    };

    void prepareSqlQueries();
    void prepareSingleSqlQuery(Query query, com::StringRef queryText);

    static int actorCallback(void* engineRef, int argc,
      char** argv, char** columnNames);

    void getActors();
    std::vector<Option> getOptionList(com::StringRef conditions);

    Response getResponse(int id);

    bool databaseOpenCalled_;
    bool databaseOpened_;
    sqlite3* database_;

    std::map<Query, std::unique_ptr<SqlQuery> > sqlQueries_;
    std::vector<Actor> actors_;

};

}

#endif