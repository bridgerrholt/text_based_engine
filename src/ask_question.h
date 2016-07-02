/// @file ask_question.h
/// Declarations of the tbe::askQuestion function and its helpers.

#ifndef TEXT_BASED_ENGINE_ASK_QUESTION_H
#define TEXT_BASED_ENGINE_ASK_QUESTION_H

#include <vector>
#include <string>

#include <dep/input_manager.h>

namespace tbe {
  namespace internal {

/// The default startNum argument.
int const RESPONSE_OPTIONS_START_NUM = 1;

  }


/** Outputs the given list of user responses.

    @param[in] responseOptions All the user response options.
    @param[in] startNum        What number the first response should be labeled.
*/
void
printResponseOptions(
  std::vector<std::string> const & responseOptions,
  int startNum = internal::RESPONSE_OPTIONS_START_NUM);



/** Gets input for selecting a number within a given range.
    The user is prompted until their answer is within [startNum, optionCount).

    @inputManager The InputManager used for standard input.
    @optionCount  The amount of possible options, used for validating the player's input.
    @startNum     Used for validating the player's input.

    @return The index that the player selected.
            Note that its within the previously provided list's range,
            meaning startNum is subtracted from the user's choice.
*/
std::size_t
getResponseIndex(
  dep::InputManager inputManager,
  std::size_t       optionCount,
  int startNum = internal::RESPONSE_OPTIONS_START_NUM);



/// Prints out @p responseOptions and gets the player's selected index.
std::size_t
askQuestion(
  dep::InputManager                inputManager,
  std::vector<std::string> const & responseOptions,
  int startNum = internal::RESPONSE_OPTIONS_START_NUM);


/// Prints out @p responseOptions and @p question, and gets the player's selected index.
/// @param question The question to be displayed before input is gathered.
std::size_t
askQuestion(
  dep::InputManager                inputManager,
  std::vector<std::string> const & responseOptions,
  std::string const &              question,
  int startNum = internal::RESPONSE_OPTIONS_START_NUM);



}

#endif