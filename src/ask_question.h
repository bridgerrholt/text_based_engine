#ifndef TEXT_BASED_ENGINE_ASK_QUESTIONS_H
#define TEXT_BASED_ENGINE_ASK_QUESTIONS_H

#include <vector>

#include <common/string_ref.h>

namespace tbe {
  namespace internal {

int const RESPONSE_OPTIONS_START_NUM = 1;

  }


/// Outputs the given list of user responses.
void
printResponseOptions(std::vector<std::string> const & responseOptions,
  int startNum = internal::RESPONSE_OPTIONS_START_NUM);


/// Gets input for selecting a number within a given range.
/// The user is prompted until their answer is within [startNum, optionCount).
std::size_t
getResponseIndex(std::size_t optionCount,
  int startNum = internal::RESPONSE_OPTIONS_START_NUM);


std::size_t
askQuestion(
  std::vector<std::string> const & responseOptions,
  int startNum = internal::RESPONSE_OPTIONS_START_NUM);


std::size_t
askQuestion(
  std::vector<std::string> const & responseOptions,
  com::StringRef question,
  int startNum = internal::RESPONSE_OPTIONS_START_NUM);

}

#endif