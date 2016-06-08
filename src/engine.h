#ifndef TEXT_BASED_ENGINE_ENGINE_H
#define TEXT_BASED_ENGINE_ENGINE_H

#include <vector>
#include <map>
#include <memory>

#include <common/string_ref.h>

#include <sqlite3.h>

#include "sql_query.h"
#include "actor.h"

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

    enum Query
    {
      GET_ACTORS
    };

    void prepareSqlQueries();
    void prepareSingleSqlQuery(Query query, com::StringRef queryText);

    static int actorCallback(void* engineRef, int argc,
      char** argv, char** azColName);

    void getActors();

    bool databaseOpenCalled_;
    bool databaseOpened_;
    sqlite3* database_;

    std::map<Query, std::unique_ptr<SqlQuery> > sqlQueries_;
    std::vector<Actor> actors_;

};

}

#endif