// Copyright 2019 Michael Johnson

#include "finalexam/triangle.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "finalexam/common.h"

namespace mjohnson {
namespace finalexam {
float80_t Triangle::side_three() const {
  // Formula for calculating the third side of a triangle given two sides and an
  // angle:
  // s3^2 = s1^2 + s2^2 - 2 * s1 * s2 * cos(angle)
  // simplifies to: s3 = sqrt(s1^2 + s2^2 - 2 * s1 * s2 * cos(angle))
  float80_t side_three = std::pow(this->side_one(), 2.0L);
  side_three += std::pow(this->side_two(), 2.0L);
  side_three -= 2.0L * this->side_one() * this->side_two() *
                std::cos(mjohnson::common::DegreesToRadians(this->angle_one()));
  side_three = std::sqrt(side_three);

  return side_three;
}

float80_t Triangle::area() const {
  // Formula for calculating the area of a triangle given two sides and an
  // angle: area = (1 / 2) * s1 * s2 * sin(angle)

  float80_t area =
      0.5L * this->side_one() * this->side_two() *
      std::sin(mjohnson::common::DegreesToRadians(this->angle_one()));

  return area;
}

Shape* Triangle::CreateEmptyDuplicate() const { return new Triangle(); }

Shape* Triangle::Add(Shape* other) const {
  if (other == nullptr) {
    throw std::invalid_argument("other must not be null");
  }

  auto other_triangle = dynamic_cast<Triangle*>(other);
  if (other_triangle == nullptr) {
    // other_triangle is null because other couldn't be casted to
    // Triangle*
    throw std::invalid_argument("a triangle can only be added to a triangle");
  }

  float80_t side_one = this->side_one() + other_triangle->side_one();
  float80_t side_two = this->side_two() + other_triangle->side_two();
  float80_t side_three = this->side_three() + other_triangle->side_three();

  // Formula for calculating an angle of a triangle given all three sides:
  // cos(angle) = (s1^2 + s2^2 - s3^2) / (2 * s1 * s2)
  float80_t new_angle = (std::pow(side_one, 2.0L) + std::pow(side_two, 2.0L) -
                         std::pow(side_three, 2.0L)) /
                        (2 * side_one * side_two);
  new_angle = std::acos(new_angle);
  new_angle = mjohnson::common::RadiansToDegrees(new_angle);

  auto new_triangle = new Triangle(side_one, side_two, new_angle);
  return new_triangle;
}

bool ValidateSideLength(float80_t length);
bool ValidateAngle(float80_t angle);

void Triangle::PromptShape() {
  std::cout << "===== TRIANGLE PARAMETERS =====" << std::endl;

  this->side_one_ = mjohnson::common::RequestInput<float80_t>(
      "Please enter the length of the first side of the triangle in inches: ",
      ValidateSideLength);
  this->side_two_ = mjohnson::common::RequestInput<float80_t>(
      "Please enter the length of the second side of the triangle in inches: ",
      ValidateSideLength);
  this->angle_ = mjohnson::common::RequestInput<float80_t>(
      "Please enter the angle between the two sides in degrees: ",
      ValidateAngle);
}

bool ValidateSideLength(float80_t length) {
  if (length < 0) {
    std::cout << std::endl
              << "ERROR: The length of the side cannot be negative."
              << std::endl
              << std::endl;
    return false;
  }

  return true;
}

bool ValidateAngle(float80_t angle) {
  if (angle <= 0.0L) {
    std::cout << std::endl
              << "ERROR: The angle must be greater than zero." << std::endl
              << std::endl;
    return false;
  }
  if (angle >= 180.0L) {
    std::cout << std::endl
              << "ERROR: The angle must be less than 180." << std::endl
              << std::endl;
    return false;
  }

  return true;
}
}  // namespace finalexam
}  // namespace mjohnson
