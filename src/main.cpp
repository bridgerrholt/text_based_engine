/// @file main.cpp
/// Creates and runs the engine.

#include <iostream>
#include <exception>

#include "engine.h"

int main(int argc, char* argv[])
{
  try {
    tbe::Engine engine;
  
    if (argc < 2) {
      throw std::runtime_error("No database file specified");
    }

    engine.loadDatabase(argv[1]);
    engine.run();

  }
  catch (std::exception& error) {
    std::cout << "Main function caught an exception:\n" <<
      error.what() << '\n' << std::endl;

    return 1;
  }

  /*tbe::sql::TemplateQuery<bool> tq {false};

  tbe::sql::Object<bool> ob {false};*/

  return 0;
}