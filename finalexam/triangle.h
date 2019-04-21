// Copyright 2019 Michael Johnson

#pragma once

#include <stdexcept>
#include <string>

#include "finalexam/common.h"
#include "finalexam/shape.h"

namespace mjohnson {
namespace finalexam {
class Triangle : public Shape {
 private:
  /**
   * The length of side one in inches.
   */
  float80_t side_one_ = 0.0L;

  /**
   * The length of side two in inches.
   */
  float80_t side_two_ = 0.0L;

  /**
   * The angle between side one and side two
   */
  float80_t angle_ = 0.0L;

 public:
  Triangle() = default;

  Triangle(float80_t side_one, float80_t side_two, float80_t angle)
      : side_one_(side_one), side_two_(side_two), angle_(angle) {
    if (side_one <= 0L) {
      throw std::invalid_argument("side_one must be greater than 0");
    }
    if (side_two <= 0L) {
      throw std::invalid_argument("side_two must be greater than 0");
    }
    if (angle <= 0L || angle >= 180L) {
      throw std::invalid_argument("angle must be in the range (0,180)");
    }
  }

  ~Triangle() override = default;

  /**
   * Returns the length of side one in inches.
   * @return The length of side one in inches.
   */
  float80_t side_one() const { return this->side_one_; }
  /**
   * Returns the length of side two in inches.
   * @return The length of side two in inches.
   */
  float80_t side_two() const { return this->side_two_; }
  /**
   * Calculates the length of side three.
   * @return The length of side three in inches.
   */
  float80_t side_three() const;

  /**
   * Returns the angle between side one and side two in degrees.
   * @return The angle between side one and side two in degrees.
   */
  float80_t angle_one() const { return this->angle_; }

  /**
   * Returns the shape's name in lowercase.
   * @return Returns the shape's name in lowercase.
   */
  std::string shape_name() const override { return "triangle"; }

  /**
   * Returns a lowercase string describing what is added when Add is called.
   * @return A lowercase string describing what is added when Add is called.
   */
  std::string add_what() const override { return "sides"; }

  /**
   * Creates an empty Triangle instance.
   * @return A new empty Triangle instance.
   */
  Shape* CreateEmptyDuplicate() const override;

  /**
   * Calculates the area of the triangle.
   * @return The area of the triangle in square inches.
   */
  float80_t area() const override;

  /**
   * Adds the three sides of two triangles and returns a new Triangle.
   * @return A new triangle, with its sides equal to the sides of the original
   * two triangles added.
   */
  Shape* Add(Shape* other) const override;

  /**
   * Prompts the user to input the parameters of the shape.
   */
  void PromptShape() override;
};
}  // namespace finalexam
}  // namespace mjohnson
