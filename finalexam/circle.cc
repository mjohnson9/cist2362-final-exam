// Copyright 2019 Michael Johnson

#include "finalexam/circle.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "finalexam/common.h"

namespace mjohnson {
namespace finalexam {
float80_t Circle::area() const {
  // Formula for calculating the area of a circle: area = pi * radius^2

  float80_t area = mjohnson::common::PI * std::pow(this->radius_, 2);

  return area;
}

Shape* Circle::CreateEmptyDuplicate() const { return new Circle(); }

Shape* Circle::Add(Shape* other) const {
  if (other == nullptr) {
    throw std::invalid_argument("other must not be null");
  }

  auto other_circle = dynamic_cast<Circle*>(other);
  if (other_circle == nullptr) {
    // other_circle is null because other couldn't be casted to
    // Triangle*
    throw std::invalid_argument("a circle can only be added to a circle");
  }

  float80_t new_radius = this->radius() + other_circle->radius();

  return new Circle(new_radius);
}

bool ValidateRadius(float80_t radius);

void Circle::PromptShape() {
  std::cout << "===== CIRCLE PARAMETERS =====" << std::endl;

  this->radius_ = mjohnson::common::RequestInput<float80_t>(
      "Please enter the radius of the circle in inches: ", ValidateRadius);
}

bool ValidateRadius(float80_t radius) {
  if (radius < 0) {
    std::cout << std::endl
              << "ERROR: The radius of the circle cannot be negative."
              << std::endl
              << std::endl;
    return false;
  }

  return true;
}
}  // namespace finalexam
}  // namespace mjohnson
