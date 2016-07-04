/// @file ask_question.h
/// Definitions of the tbe::askQuestion function and its helpers.

#include "ask_question.h"

#include <iostream>
#include <stdexcept>

#include <dep/is_int.h>

namespace tbe {

void
printResponseOptions(
  std::vector<std::string> const & responseOptions,
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
getResponseIndex(
  dep::InputManager inputManager,
  std::size_t optionCount,
  int startNum)
{
  std::string input;
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
askQuestionShell(
  dep::InputManager inputManager,
  std::vector<std::string> const & responseOptions,
  int startNum,
  com::StringRef fullOutput = "")
{
  printResponseOptions(responseOptions, startNum);

  std::cout << fullOutput;
  
  return getResponseIndex(inputManager, responseOptions.size(), startNum);
}



std::size_t
askQuestion(
  dep::InputManager inputManager,
  std::vector<std::string> const & responseOptions,
  int startNum)
{
  return askQuestionShell(inputManager, responseOptions, startNum);
}


std::size_t
askQuestion(
  dep::InputManager inputManager,
  std::vector<std::string> const & responseOptions,
  com::StringRef question,
  int startNum)
{
  return askQuestionShell(inputManager, responseOptions,
                          startNum, question + "\n");
}



}