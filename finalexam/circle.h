// Copyright 2019 Michael Johnson

#pragma once

#include <stdexcept>
#include <string>

#include "finalexam/common.h"
#include "finalexam/shape.h"

namespace mjohnson {
namespace finalexam {
class Circle : public Shape {
 private:
  /**
   * The angle between side one and side two
   */
  float80_t radius_ = 0.0L;

 public:
  Circle() = default;

  explicit Circle(float80_t radius) : radius_(radius) {
    if (radius <= 0.0L) {
      throw std::invalid_argument("radius must be greater than 0");
    }
  }

  ~Circle() override = default;

  /**
   * Returns the radius of the circle in inches.
   * @return The radius in inches.
   */
  float80_t radius() const { return this->radius_; }

  /**
   * Returns the shape's name in lowercase.
   * @return Returns the shape's name in lowercase.
   */
  std::string shape_name() const override { return "circle"; }

  /**
   * Returns a lowercase string describing what is added when Add is called.
   * @return A lowercase string describing what is added when Add is called.
   */
  std::string add_what() const override { return "radii"; }

  /**
   * Creates an empty Circle instance.
   * @return A new empty Circle instance.
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
