// Copyright 2019 Michael Johnson

#include "finalexam/common.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

namespace mjohnson {
namespace common {
// This is a specialization for string. It reads entire lines instead of a
// single word.
template <>
std::string RequestInput<std::string>(
    const std::string& prompt,
    const std::function<bool(std::string)>& validator) {
  bool valid = true;
  std::string response;
  do {
    std::cout << prompt;
    std::getline(std::cin, response);

    if (validator) {  // Validator has a bool operator that tells us whether or
                      // not the function is empty
      valid = validator(response);
    } else {
      valid = true;
    }
  } while (!valid);

  return response;
}

bool ValidateInputIsDigits(std::string input);

template <>
float80_t RequestInput<float80_t>(
    const std::string& prompt,
    const std::function<bool(float80_t)>& validator) {
  while (true) {  // Create an infinite loop that we'll exit by returning
    auto input = RequestInput<std::string>(prompt, ValidateInputIsDigits);

    float80_t input_number;
    try {
      input_number = std::stold(input);
    } catch (const std::invalid_argument& ex) {
      std::cout << std::endl
                << "ERROR: The value you gave is not a valid decimal number."
                << std::endl
                << std::endl;
      continue;
    } catch (const std::out_of_range& ex) {
      std::cout << std::endl
                << "ERROR: The value you gave is outside of the representable "
                   "range. Please enter a smaller value."
                << std::endl
                << std::endl;
      continue;
    }

    if (!validator(input_number)) {
      continue;
    }

    return input_number;
  }
}

bool ValidateInputIsDigits(std::string input) {
  TrimString(&input);

  if (!IsDigits(input)) {
    std::cout << std::endl
              << "ERROR: You must input only digits." << std::endl
              << std::endl;
    return false;
  }

  return true;
}

void ClearInputWhitespace() {
  char c = static_cast<char>(std::cin.peek());
  if (std::isspace(c) == 0) {
    // The next character isn't whitespace; leave it alone
    return;
  }
  std::cin.ignore();  // Ignore the whitespace
}

void ClearInvalidInput() {
  std::cin.clear();  // clear the error from cin
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n');  // Ignore all of the user input currently in the
                          // buffer up to the next new line.
}

// ValidateContinueResponse is a validation function for RequestInput. It
// validates that a response to the continue question can be used.
bool ValidateContinueResponse(const std::string& response);

bool RequestContinue() {
  while (true) {
    auto response = RequestInput<std::string>(
        "Would you like to run the program again? [y/N] ",
        ValidateContinueResponse);
    if (response.empty()) {
      return false;  // The default option is to not continue
    }

    // Lowercase the response to make it easier to compare
    std::transform(response.begin(), response.end(), response.begin(),
                   ::tolower);
    if (response == "y" || response == "yes") {
      return true;
    }
    if (response == "n" || response == "no") {
      return false;
    }

    // We should never reach this point
    throw std::invalid_argument("response");
  }
}

bool ValidateContinueResponse(const std::string& response) {
  if (response.empty()) {
    // Shortcut; we allow empty responses
    return true;
  }

  std::string modified_response = response;  // Copy the response string

  // Lowercase the response to make it easier to compare
  std::transform(modified_response.begin(), modified_response.end(),
                 modified_response.begin(), ::tolower);

  const bool is_valid =
      (modified_response == "y" || modified_response == "yes" ||
       modified_response == "n" || modified_response == "no");
  if (!is_valid) {
    std::cout << response
              << " is an invalid response. Available responses are yes, y, "
                 "no, or n."
              << std::endl
              << std::endl;
  }

  return is_valid;
}

void ClearScreen() {
  // It feels nasty forking a process to clear the screen, but it's a better
  // alternative to including something like ncurses
#if defined(_WIN32) || defined(_WIN64)
  system("CLS");
#elif defined(unix) || defined(__unix__) || defined(__unix) || \
    (defined(__APPLE__) && defined(__MACH__))
  system("clear");
#else
#error "Operating system not supported"
#endif  // End of OS detection
}

void Pause() {
  // Wait for a line of input and ignore the result.
  RequestInput<std::string>("Press enter to continue.", nullptr);
}

float80_t DegreesToRadians(float80_t degrees) {
  return (degrees * PI / 180.0L);
}

float80_t RadiansToDegrees(float80_t radians) {
  return (radians * 180.0L / PI);
}

bool ValidateStringNotEmpty(const std::string& message,
                            const std::string& str) {
  std::string str_copy(str);
  TrimString(&str_copy);
  if (str.empty()) {
    std::cout << message;
    return false;
  }

  return true;
}

void TrimString(std::string* str) {
  str->erase(str->begin(), std::find_if(str->begin(), str->end(), [](int c) {
               return std::isspace(c) == 0;
             }));  // Erase the string from the beginning until the last
                   // whitespace character
  str->erase(std::find_if(str->rbegin(), str->rend(),
                          [](int c) { return std::isspace(c) == 0; })
                 .base(),
             str->end());  // Erase the string from the last whitespace
                           // character (searching right to left) to the end
}

void LowerString(std::string* str) {
  std::transform(str->begin(), str->end(), str->begin(), ::tolower);
}

bool IsDigits(const std::string& str) {
  bool first = true;
  bool had_decimal = false;

  for (const char c : str) {
    if (first) {
      first = false;
      if (c == '-') {
        // negative is allowed as the first character
        continue;
      }
    }
    if (c == '.' && !had_decimal) {
      // One decimal point is allowed
      had_decimal = true;
      continue;
    }
    if (std::isdigit(c) == 0) {
      return false;
    }
  }

  return true;
}
}  // namespace common
}  // namespace mjohnson
