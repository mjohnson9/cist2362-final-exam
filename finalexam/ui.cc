// Copyright 2019 Michael Johnson

#include "finalexam/ui.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

#include "finalexam/circle.h"
#include "finalexam/common.h"
#include "finalexam/shape.h"
#include "finalexam/triangle.h"

namespace mjohnson {
namespace finalexam {
// Forward declarations for functions that are only needed in the local scope
Shape* PromptShapeType();
bool RequestAdd(const Shape* shape);

Shape* CreateEmptyDuplicate(Shape* shape);

// Input validation functions
bool ValidateShapeType(const std::string& response);
bool ValidateYesNo(const std::string& response);

// Function definitions

void Run() {
  do {
    mjohnson::common::ClearScreen();
    Shape* shape = PromptShapeType();

    mjohnson::common::ClearScreen();
    shape->PromptShape();

    mjohnson::common::ClearScreen();
    std::cout << "The area of your " << shape->shape_name() << " is "
              << std::setprecision(1) << std::fixed << shape->area()
              << " square inches." << std::endl;
    mjohnson::common::Pause();

    mjohnson::common::ClearScreen();
    if (!RequestAdd(shape)) {
      // The user didn't want to add another shape, skip back to the beginning
      // of the loop
      delete shape;
      continue;
    }

    Shape* shape_two = shape->CreateEmptyDuplicate();

    mjohnson::common::ClearScreen();
    shape_two->PromptShape();

    mjohnson::common::ClearScreen();
    std::cout << "The area of your second " << shape_two->shape_name() << " is "
              << std::setprecision(1) << std::fixed << shape_two->area()
              << " square inches." << std::endl;
    mjohnson::common::Pause();

    Shape* added_shape = shape->Add(shape_two);

    mjohnson::common::ClearScreen();
    std::cout << "By adding the " << shape->add_what() << " of your "
              << shape->shape_name() << "s, you created a "
              << added_shape->shape_name() << " with an area of "
              << std::setprecision(1) << std::fixed << added_shape->area()
              << " square inches." << std::endl;
    mjohnson::common::Pause();

    delete shape;
    delete shape_two;
    delete added_shape;
  } while (mjohnson::common::RequestContinue());
}

Shape* PromptShapeType() {
  auto user_choice = mjohnson::common::RequestInput<std::string>(
      "What shape would you like to calculate the area of?\n[A] Circle\n[B] "
      "Triangle\nYour response: ",
      ValidateShapeType);

  mjohnson::common::TrimString(&user_choice);
  mjohnson::common::LowerString(&user_choice);

  if (user_choice == "a") {
    auto circle = new Circle();
    return circle;
  }
  if (user_choice == "b") {
    auto triangle = new Triangle();
    return triangle;
  }

  throw std::runtime_error("should not reach the end of PromptShapeType");
}

bool RequestAdd(const Shape* shape) {
  auto user_choice = mjohnson::common::RequestInput<std::string>(
      "Would you like to add another " + shape->shape_name() + "? [y/n] ",
      ValidateYesNo);
  mjohnson::common::TrimString(&user_choice);
  mjohnson::common::LowerString(&user_choice);

  return user_choice == "y";
}

bool ValidateShapeType(const std::string& response) {
  std::string response_copy(response);
  mjohnson::common::TrimString(&response_copy);
  mjohnson::common::LowerString(&response_copy);

  if (response_copy.empty()) {
    std::cout << std::endl
              << "ERROR: You must enter a response." << std::endl
              << std::endl;
    return false;
  }

  if (response_copy != "a" && response_copy != "b") {
    std::cout << std::endl
              << "ERROR: \"" << response
              << "\" is not a valid choice. Please choose A or B." << std::endl
              << std::endl;
    return false;
  }

  return true;
}

bool ValidateYesNo(const std::string& response) {
  std::string response_copy(response);
  mjohnson::common::TrimString(&response_copy);
  mjohnson::common::LowerString(&response_copy);

  if (response_copy.empty()) {
    std::cout << std::endl
              << "ERROR: You must enter a response." << std::endl
              << std::endl;
    return false;
  }

  if (response_copy != "y" && response_copy != "n") {
    std::cout << std::endl
              << "ERROR: \"" << response
              << "\" is not a valid choice. Please choose Y or N." << std::endl
              << std::endl;
    return false;
  }

  return true;
}
}  // namespace finalexam
}  // namespace mjohnson
