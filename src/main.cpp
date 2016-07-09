/// @file main.cpp
/// Creates and runs the engine.

#include <iostream>
#include <exception>

#include "engine/engine.h"

int main(int argc, char* argv[])
{
  try {
    tbe::Engine engine;
  
    // The user is expected to pass the path and name of the database file as the first parameter.
    if (argc < 2) {
      throw std::runtime_error("No database file specified");
    }

    engine.run(argv[1]);
  }

  catch (std::exception const & e) {
    std::cout << "Main function caught an exception:\n" <<
      e.what() << '\n' << std::endl;

    // Allows the operating system to catch it (the stack still safely unwinds).
    throw;
  }

  // Unhandled exception case.
  catch (...) {
    std::cout << "Main function caught an unhandled exception\n" << std::endl;

    throw;
  }

  return 0;
}