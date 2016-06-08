#include "full_wrapper.h"

#include <iostream>
#include <string>
#include <stdexcept>

namespace tbe {

FullWrapper::FullWrapper()
{
  initialize();
}



FullWrapper::~FullWrapper()
{
  
}



void
FullWrapper::initialize()
{
  std::cout << "Core initialization begun.\n";



  std::cout << "Core initialization succeeded.\n";
}



}