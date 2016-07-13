/// @file ask_question.h
/// Definitions of the overloaded function tbe::askQuestion() and its
/// lower-level support functions.

#include "ask_question.h"

#include <iostream>
#include <stdexcept>

#include <dep/input_manager.h>
#include <dep/is_int.h>

namespace {

using namespace tbe;

std::size_t
askQuestionShell(
  dep::InputManager          inputManager,
  ResponseOptionList const & responseOptions,
  std::size_t                startNum,
  std::string        const & fullOutput = "")
{
  printResponseOptions(responseOptions, startNum);

  std::cout << fullOutput;
  
  return getResponseIndex(inputManager, responseOptions.size(), startNum);
}


std::size_t
askQuestionShell(
  dep::InputManager   inputManager,
  std::size_t         optionCount,
  std::size_t         startNum,
  std::string const & fullOutput = "")
{
  std::cout << fullOutput;
  
  return getResponseIndex(inputManager, optionCount, startNum);
}



std::size_t
askQuestionShell(
  std::string const & input,
  std::size_t         optionCount,
  std::size_t         startNum,
  std::string const & fullOutput = "")
{
  std::cout << fullOutput;

  return getResponseIndex(input, optionCount, startNum);
}

}



namespace tbe {

void
printResponseOptions(
  ResponseOptionList const & responseOptions,
  std::size_t                startNum)
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
getResponseIndex(
  dep::InputManager inputManager,
  std::size_t       optionCount,
  std::size_t       startNum)
{
  std::size_t index;

  while (true) {
    std::cout << "> ";
    std::string input = inputManager.get().trim().str();

    if (dep::isInt(input)) {
      index = std::stoi(input);
      if (index >= startNum && index < optionCount+startNum)
        break;
    }
  }

  return index - startNum;
}


std::size_t
getResponseIndex(
  std::string const & input,
  std::size_t         optionCount,
  std::size_t         startNum)
{
  std::size_t index;

  while (true) {
    if (dep::isInt(input)) {
      index = std::stoi(input);
      if (index >= startNum && index < optionCount+startNum)
        break;
    }
  }

  return index - startNum;
}


bool
processResponseIndex(
  std::string const & input,
  std::size_t         optionCount,
  std::size_t       & optionIndex,
  std::size_t startNum)
{
  if (dep::isInt(input)) {
    optionIndex = std::stoi(input);
    if (optionIndex >= startNum && optionIndex < optionCount+startNum)
      return true;
  }

  return false;
}




std::size_t
askQuestion(
  dep::InputManager                inputManager,
  std::vector<std::string> const & responseOptions,
  std::size_t                      startNum)
{
  return askQuestionShell(inputManager, responseOptions, startNum);
}


std::size_t
askQuestion(
  dep::InputManager          inputManager,
  ResponseOptionList const & responseOptions,
  std::string        const & question,
  std::size_t                startNum)
{
  return askQuestionShell(inputManager, responseOptions,
                          startNum, question + "\n");
}


std::size_t
askQuestion(
  dep::InputManager   inputManager,
  std::size_t         optionCount,
  std::string const & question,
  std::size_t         startNum)
{
  return askQuestionShell(inputManager, optionCount,
                          startNum, question + "\n");
}


std::size_t
askQuestion(
  std::string const & input,
  std::size_t         optionCount,
  std::string const & question,
  std::size_t startNum)
{
  return askQuestionShell(input, optionCount,
                          startNum, question + "\n");
}





}