#include <iostream>
#include <exception>

#include <xercesc/util/PlatformUtils.hpp>

#include "full_wrapper.h"

using namespace xercesc;

int main(int argc, char* argv[])
{
  try {
    tbe::FullWrapper fullWrapper;
  }
  catch (std::exception& error) {
    std::cout << "Main function caught an exception:\n" <<
      error.what();
  }
    

  // Other terminations and cleanup.
  return 0;
}