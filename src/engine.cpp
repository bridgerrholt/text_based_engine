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
  std::cerr << "about to clear\n";
  sqlQueries_.clear();
  std::cerr << "cleared\n";

  closeDatabase();

  std::cerr << "Engine destructed\n";
}



void
Engine::loadDatabase(com::StringRef fileName)
{
  closeDatabase();
  openDatabase(fileName);
  getActors();

  for (auto i : actors_) {
    std::cerr << i.name << ' ' << i.next << '\n';
  }
}



void
Engine::run()
{
  std::size_t actorCount = actors_.size();
  if (actorCount == 0)
    return;

  std::string input;
  std::size_t actorIndex;
  while (true) {
    std::vector<std::string> actorNames;
    actorNames.push_back("QUIT");
    for (auto i : actors_) actorNames.push_back(i.name);

    std::size_t actorIndex =
      askQuestion(actorNames, "Who would you like to talk to?", 0);

    if (actorIndex == 0) break;

    actorIndex -= 1;

    int next = actors_[actorIndex].next;
    std::cerr << next << '\n';

    if (next == 0) {
      std::cout << actorNames[actorIndex] <<
        " doesn't want to speak right now.\n";
      continue;
    }

    std::cerr << "Wants to speak\n";

    while (next != 0) {
      Response response = getResponse(next);
      std::cout << '\n' << actors_[actorIndex].name << ": " <<
        response.text;


      std::string inputString;
      std::getline(std::cin, inputString);

      std::cout << "\n\n";

      if (response.next == 0)
        break;

      std::string statement = "option_list_id = " +
        std::to_string(response.next);
      std::cerr << statement << '\n';

      std::vector<Option> options =
        getOptionList(statement);

      std::cerr << "Got options\n";

      std::vector<std::string> optionTextList;
      for (auto i : options) optionTextList.push_back(i.textDisplay);
      std::cerr << "Option text list\n";

      std::size_t optionIndex = askQuestion(optionTextList);
      std::cout << '\n' << options[optionIndex].textSpeak << "\n\n";

      next = options[optionIndex].next;
    }

    /*std::string statement = "next = " + std::to_string(next);
    std::cerr << statement << '\n';

    std::vector<Option> options =
      getOptionList(statement);

    std::cerr << "Got options\n";

    std::vector<std::string> optionTextList;
    for (auto i : options) optionTextList.push_back(i.textDisplay);
    std::cerr << "Option text list\n";

    std::size_t optionIndex = askQuestion(optionTextList);
    std::cerr << "\n";

    break;*/
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
    std::cerr << "Gonna close\n";
    while (sqlite3_close(database_) != SQLITE_OK) {
      std::cerr << "Failed close\n";
    }
  }

  std::cerr << "Closed\n";

  databaseOpenCalled_ = false;
  databaseOpened_ = false;
}



void
printResponseOptions(std::vector<std::string> const & responseOptions,
  int startNum)
{
  std::cerr << "printResponseOptions\n";
  std::size_t optionCount = responseOptions.size();
  std::cerr << optionCount << '\n';
  if (optionCount == 0)
    throw std::runtime_error("Question with no response options.\n ");

  for (std::size_t i = 0; i < optionCount; ++i) {
    std::cout << startNum + i << ": " << responseOptions[i] << '\n';
  }

  std::cerr << "Outputted\n";
}



std::size_t
getResponseIndex(std::size_t optionCount, int startNum)
{
  std::string input;
  std::size_t index;

  while (true) {
    std::cout << "> ";
    std::cin >> input;

    if (dep::isInt(input)) {
      index = std::stoi(input);
      if (index >= startNum && index < optionCount+startNum)
        break;
    }
  }

  return index - startNum;
}



std::size_t
Engine::askQuestion(
  std::vector<std::string> const & responseOptions,
  int startNum)
{
  printResponseOptions(responseOptions, startNum);
  
  return getResponseIndex(responseOptions.size(), startNum);
}

std::size_t
Engine::askQuestion(
  std::vector<std::string> const & responseOptions,
  com::StringRef question,
  int startNum)
{
  printResponseOptions(responseOptions, startNum);

  std::cout << question << '\n';

  return getResponseIndex(responseOptions.size(), startNum);
}



void
Engine::prepareSqlQueries()
{
  sqlQueries_.clear();
  //prepareSingleSqlQuery(GET_ACTORS, "SELECT * FROM actors;");
}



void
Engine::prepareSingleSqlQuery(Query query, com::StringRef queryText)
{
  sqlQueries_.emplace(query,
    std::unique_ptr<SqlQuery>(new SqlQuery(database_, queryText)));
}



int
Engine::actorCallback(void* engineRef, int argc,
  char** argv, char** columnNames)
{
  Actor actor = { "", 0 };

  for (int i = 0; i < argc; ++i) {
    std::string colNameString = std::string(columnNames[i]);

    if (colNameString == "name") {
      actor.name = std::string(argv[i]);
    }
    else if (colNameString == "next") {
      actor.next = std::stoi(argv[i]);
    }
  }

  ((Engine*) engineRef)->actors_.push_back(actor);

  return 0;
}



int
optionCallback(void* listRef, int argc,
  char** argv, char** columnNames)
{
  Option option = { 0, 0, "", "", 0 };
  std::cerr << "optionCallback: argc=" + std::to_string(argc) << '\n';

  for (int i = 0; i < argc; ++i) {
    std::string colNameString = std::string(columnNames[i]);

    if (colNameString == "character_id")
      option.characterId = std::stoi(argv[i]);
    else if (colNameString == "option_list_id")
      option.optionListId = std::stoi(argv[i]);
    else if (colNameString == "text_display")
      option.textDisplay = std::string(argv[i]);
    else if (colNameString == "text_speak")
      option.textSpeak = std::string(argv[i]);
    else if (colNameString == "next")
      option.next = std::stoi(argv[i]);
  }

  ((std::vector<Option>*) listRef)->push_back(option);

  std::cerr << option.textDisplay << '\n';

  return 0;
}



int
responseCallback(void* responseRefVoid, int argc,
  char** argv, char** columnNames)
{
  std::cerr << responseRefVoid << '\n';
  Response* responseRef = (Response*) responseRefVoid;
  std::cerr << responseRef << '\n';
  for (int i = 0; i < argc; ++i) {
    std::string colNameString = std::string(columnNames[i]);

    if (colNameString == "text")
      responseRef->text = std::string(argv[i]);
    else if (colNameString == "next")
      responseRef->next = std::stoi(argv[i]);
  }

  return 0;
}



void
Engine::getActors()
{
  assert(databaseOpened_);

  actors_.clear();


  char* errorMessage = 0;
  int resultCode = sqlite3_exec(database_, "SELECT * FROM actors;",
    actorCallback, (void*)this, &errorMessage);

  if (resultCode != SQLITE_OK) {
    std::string exceptionMessage =
      "SQL error getting actors:\n" + std::string(errorMessage);
    sqlite3_free(errorMessage);
    throw std::runtime_error(exceptionMessage);
  }
}



std::vector<Option>
Engine::getOptionList(com::StringRef conditions)
{
  assert(databaseOpened_);

  std::vector<Option> optionList;

  std::string sql = "SELECT * FROM options WHERE " + conditions + ';';
  std::cerr << sql << '\n';

  char* errorMessage = 0;
  int resultCode = sqlite3_exec(database_,
    sql.c_str(),
    optionCallback, (void*)&optionList, &errorMessage);

  std::cerr << resultCode << '\n';

  if (resultCode != SQLITE_OK) {
    std::string exceptionMessage =
      "SQL error getting options:\n" + std::string(errorMessage);
    sqlite3_free(errorMessage);
    throw std::runtime_error(exceptionMessage);
  }
  
  return optionList;
}



Response
Engine::getResponse(int id)
{
  assert(databaseOpened_);

  Response returnResponse;

  std::string sql = "SELECT * FROM responses "
    "WHERE id = " + std::to_string(id) + ';';
  std::cerr << sql << '\n';

  char* errorMessage = 0;
  int resultCode = sqlite3_exec(database_,
    sql.c_str(),
    responseCallback, (void*)&returnResponse, &errorMessage);

  std::cerr << resultCode << '\n';

  if (resultCode != SQLITE_OK) {
    std::string exceptionMessage =
      "SQL error getting response (id = " + std::to_string(id) +
      "):\n" + std::string(errorMessage);
    sqlite3_free(errorMessage);
    throw std::runtime_error(exceptionMessage);
  }
  
  return returnResponse;
}



}
