/// @file ask_question.h
/// Declarations of the overloaded function tbe::askQuestion() and its
/// lower-level support functions.

#ifndef TEXT_BASED_ENGINE_ENGINE_ASK_QUESTION_H
#define TEXT_BASED_ENGINE_ENGINE_ASK_QUESTION_H

#include <vector>
#include <string>

namespace dep {

class InputManager;

}



namespace tbe {
  namespace internal {

/// The default startNum argument.
std::size_t const RESPONSE_OPTIONS_START_NUM = 1;

  }


typedef std::vector<std::string> ResponseOptionList;


/// Outputs the given list of user responses.
///
/// @param[in] responseOptions All the user response options.
/// @param[in] startNum        What number the first response should be labeled as.
void
printResponseOptions(
  ResponseOptionList const & responseOptions,
  std::size_t startNum = internal::RESPONSE_OPTIONS_START_NUM);



/// Gets input for selecting a number within a given range.
/// The user is prompted until their answer is within [startNum, optionCount).
///
/// @param[in] inputManager The InputManager used for standard input.
/// @param[in] optionCount  The amount of possible options,
///                         used for validating the player's input.
/// @param[in] startNum     Used for validating the player's input.
///
/// @return The index that the player selected.
///         Note that its within the previously provided list's range,
///         meaning startNum is subtracted from the user's choice.
std::size_t
getResponseIndex(
  dep::InputManager inputManager,
  std::size_t       optionCount,
  std::size_t startNum = internal::RESPONSE_OPTIONS_START_NUM);


std::size_t
getResponseIndex(
  std::string const & input,
  std::size_t         optionCount,
  std::size_t startNum = internal::RESPONSE_OPTIONS_START_NUM);


bool
processResponseIndex(
  std::string const & input,
  std::size_t         optionCount,
  std::size_t       & optionIndex,
  std::size_t startNum = internal::RESPONSE_OPTIONS_START_NUM);




/// Prints out @p responseOptions and gets the player's selected index.
std::size_t
askQuestion(
  dep::InputManager                inputManager,
  ResponseOptionList const & responseOptions,
  std::size_t startNum = internal::RESPONSE_OPTIONS_START_NUM);


/// Prints out @p responseOptions and @p question, and gets the player's selected index.
/// @param question The question to be displayed before input is gathered.
std::size_t
askQuestion(
  dep::InputManager                inputManager,
  ResponseOptionList const & responseOptions,
  std::string              const & question,
  std::size_t startNum = internal::RESPONSE_OPTIONS_START_NUM);


std::size_t
askQuestion(
  dep::InputManager   inputManager,
  std::size_t         optionCount,
  std::string const & question,
  std::size_t startNum = internal::RESPONSE_OPTIONS_START_NUM);


std::size_t
askQuestion(
  std::string const & input,
  std::size_t         optionCount,
  std::string const & question,
  std::size_t startNum = internal::RESPONSE_OPTIONS_START_NUM);



}

#endif