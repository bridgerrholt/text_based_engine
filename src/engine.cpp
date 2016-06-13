/// @file engine.cpp
/// Definition of the Engine class.

#include "engine.h"

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cctype>

#include <dep/check_file_exists.h>
#include <dep/is_int.h>
#include <dep/wait.h>

#include "ask_question.h"

namespace tbe {

Engine::Engine() :
  locale_(""),
  inputManager_(locale_),
  databaseOpened_(false),
  database_(0),
  wait_(500)
{

}



Engine::~Engine()
{
  closeDatabase();

  std::cerr << "Engine destructed\n";
}



void
Engine::loadDatabase(com::StringRef fileName)
{
  openDatabase(fileName);

  sql::Actor actor(database_);
  actors_ = actor.run();

  for (auto i : actors_) {
    std::cerr << i.name << ' ' << i.introId << '\n';
  }
}



void
Engine::run()
{
  // Exit the function if the database doesn't contain any characters.
  std::size_t actorCount = actors_.size();
  if (actorCount == 0) {
    std::cout << "Nobody seems to be around.\n";
    return;
  }

  // primaryOptions is initialized before the main loop and resized every iteration.
  std::vector<std::string> primaryOptions;

  // constantOptionsCount specifies how many options remain through every iteration,
  // primaryOptions is resized to it every iteration.
  std::size_t constantOptionsCount = 1;

  primaryOptions.push_back("QUIT");


  // The main game loop.
  // Upon every iteration it shows the list of actors and lets the player talk to one.
  while (true) {
    // All the old actors are removed and all the current actors are added.
    primaryOptions.resize(constantOptionsCount);
    for (auto i : actors_)
      primaryOptions.push_back(i.name);

    // The player selects an index of primaryOptions.
    std::size_t optionIndex =
      askQuestion(inputManager_, primaryOptions,
                 "Who would you like to talk to?", 0);

    // All the constant options are handled.
    if (optionIndex == 0) break;

    // The index is now mapped to actors_ since the constant options are cleared.
    sql::Actor::Data& currentActor = actors_[optionIndex-constantOptionsCount];
    optionIndex -= constantOptionsCount;

    // The ID of the next row to query.
    int next = currentActor.introId;
    std::cerr << next << '\n';

    // If the intro ID is 0, that indicates no conversation will take place.
    if (next == 0) {
      std::cout << currentActor.name <<
        " doesn't want to speak right now.\n";

      // Brings it back to the actor menu.
      continue;
    }

    std::cerr << "Wants to speak\n";

    // The conversation is ongoing until one of the actions points to the ID of 0.
    while (next != 0) {
      // Gets the ID pointed to by next.
      sql::Response responseCall({database_,
        "id = " + std::to_string(next)});
      sql::Response::Data response = responseCall.run().at(0);

      // Outputs the actor's dialogue.
      std::cout << '\n' <<
        currentActor.name << ": " <<
        response.textSpeak << wait_ << '\n';

      if (response.nextId == 0)
        break;

      std::string statement = "option_list_id = " +
        std::to_string(response.nextId);
      std::cerr << statement << '\n';

      sql::Option optionCall({database_, statement});

      std::vector<sql::Option::Data> options =
        optionCall.run();

      std::cerr << "Got options\n";

      std::vector<std::string> optionTextList;
      for (auto i : options) optionTextList.push_back(i.textDisplay);
      std::cerr << "Option text list\n";

      std::size_t optionIndex = askQuestion(inputManager_, optionTextList);
      std::cout << '\n' << options[optionIndex].textSpeak << '\n' << wait_;

      next = options[optionIndex].nextId;
    }

  }
}



void
Engine::openDatabase(com::StringRef fileName)
{
  // Closes the database if it's open.
  closeDatabase();

  if (!dep::checkFileExists(fileName)) {
    throw std::runtime_error(
      "Database file can't be found:\n " +
        fileName
    );
  }

  // Attempts to open the database.
  int resultCode = sqlite3_open_v2(
    fileName.c_str(), &database_,
    SQLITE_OPEN_READWRITE, 0
  );

  if (resultCode != SQLITE_OK) {
    // Resources must be freed even on failure.
    sqlite3_close(database_);

    throw std::runtime_error(
      "Can't open database:\n " +
        fileName + "\n"
      "because:\n" +
       sqlite3_errmsg(database_)
    );
  }

  else databaseOpened_ = true;
}



void
Engine::closeDatabase()
{
  if (databaseOpened_) {
    std::cerr << "About to close opened database\n";

    // Shouldn't be anything but SQLITE_OK.
    if (sqlite3_close_v2(database_) != SQLITE_OK) {
      std::cerr << "Database couldn't close\n";
    }

    std::cerr << "Closed database\n";
  }


  databaseOpened_ = false;
}



}
