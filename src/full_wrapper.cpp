#include "full_wrapper.h"

#include <iostream>
#include <string>
#include <stdexcept>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace xercesc;

namespace tbe {

FullWrapper::FullWrapper()
{
  initialize();
}



FullWrapper::~FullWrapper()
{
  
  XMLPlatformUtils::Terminate();
}



void
FullWrapper::initialize()
{
  std::cout << "Core initialization begun.\n";

  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    char*       message    = XMLString::transcode(toCatch.getMessage());
    std::string messageStr = std::string(message);

    XMLString::release(&message);

    throw std::runtime_error(
      "FullWrapper initialization (core initialization) failed:\n" +
      messageStr);
  }

  std::cout << "Core initialization succeeded.\n";
}



}