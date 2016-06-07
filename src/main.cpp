#include <iostream>
#include <exception>

#include <xercesc/util/PlatformUtils.hpp>

#include "full_wrapper.h"
#include "engine.h"

using namespace xercesc;

int main(int argc, char* argv[])
{
  try {
    tbe::FullWrapper fullWrapper;
    tbe::Engine      engine;
  
    if (argc < 2) {
      throw std::runtime_error("No JSON config file specified");
    }

    engine.loadConfig(argv[1]);

  }
  catch (std::exception& error) {
    std::cout << "Main function caught an exception:\n" <<
      error.what();
  }

  return 0;
}