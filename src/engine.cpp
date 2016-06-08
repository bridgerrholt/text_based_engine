#include "engine.h"

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cctype>

#include <dep/check_file_exists.h>
#include <dep/is_int.h>

namespace tbe {

Engine::Engine() :
  databaseOpenCalled_(false),
  databaseOpened_(false),
  database_(0)
{

}



Engine::~Engine()
{
  std::cout << "about to clear\n";
  sqlQueries_.clear();
  std::cout << "cleared\n";

  closeDatabase();
}



void
Engine::loadDatabase(com::StringRef fileName)
{
  closeDatabase();
  openDatabase(fileName);
  getActors();

  for (auto i : actors_) {
    std::cout << i.name << ' ' << i.introListId << '\n';
  }
}



void
Engine::run()
{
  std::string input;
  std::size_t actorIndex;
  while (true) {
    std::size_t actorCount = actors_.size();
    for (std::size_t i = 0; i < actorCount; ++i) {
      std::cout << i + 1 << ": " << actors_[i].name << '\n';
    }
    std::cout << "Who would you like to talk to?\n";

    while (true) {
      std::cout << "> ";
      std::cin >> input;

      if (dep::isInt(input)) {
        actorIndex = std::stoi(input);
        if (actorIndex >= 1 && actorIndex <= actorCount)
          break;
      }
    }

    break;
  }
}



void
Engine::openDatabase(com::StringRef fileName)
{
  if (!dep::checkFileExists(fileName)) {
    throw std::runtime_error("Database file doesn't exist:\n " + fileName);
  }

  int resultCode = sqlite3_open(fileName.c_str(), &database_);
  databaseOpenCalled_ = true;

  if (resultCode != SQLITE_OK) {
    sqlite3_close(database_);
    throw std::runtime_error("Can't open database:\n " + fileName);
  }

  databaseOpened_ = true;

  prepareSqlQueries();
}



void
Engine::closeDatabase()
{
  if (databaseOpenCalled_ || databaseOpened_) {
    while (sqlite3_close(database_) != SQLITE_OK) {}
  }

  databaseOpenCalled_ = false;
  databaseOpened_ = false;
}



void
Engine::prepareSqlQueries()
{
  sqlQueries_.clear();
  prepareSingleSqlQuery(GET_ACTORS, "SELECT * FROM actors;");
}



void
Engine::prepareSingleSqlQuery(Query query, com::StringRef queryText)
{
  sqlQueries_.emplace(query,
    std::unique_ptr<SqlQuery>(new SqlQuery(database_, queryText)));
}



int Engine::actorCallback(void* engineRef, int argc,
  char** argv, char** azColName)
{
  Actor actor = { "", 0 };

  for (int i = 0; i < argc; ++i) {
    std::string colNameString = std::string(azColName[i]);
    if (colNameString == "name") {
      actor.name = std::string(argv[i]);
    }
    else if (colNameString == "intro_list_id") {
      actor.introListId = std::stoi(argv[i]);
    }
  }

  ((Engine*) engineRef)->actors_.push_back(actor);

  return 0;
}



void
Engine::getActors()
{
  assert(databaseOpened_);

  actors_.clear();


  char* errorMessage = 0;
  int resultCode = sqlite3_exec(database_, "SELECT * FROM actors",
    actorCallback, (void*)this, &errorMessage);

  if (resultCode != SQLITE_OK) {
    std::string exceptionMessage =
      "SQL error getting actors:\n" + std::string(errorMessage);
    sqlite3_free(errorMessage);
    throw std::runtime_error(exceptionMessage);
  }
}



}
