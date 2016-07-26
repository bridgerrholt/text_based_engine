/// @file main.cpp
/// Creates and runs the engine.

#include <iostream>
#include <exception>

#include "engine/engine.h"

int main(int argc, char* argv[])
{
  try {
    tbe::Engine engine { argc, argv };
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