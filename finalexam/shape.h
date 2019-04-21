// Copyright 2019 Michael Johnson

#pragma once

#include <string>

#include "finalexam/common.h"

class Shape {
 public:
  virtual ~Shape() = default;

  /**
   * Calculates the area of the shape.
   * @return The area of the shape in square inches.
   */
  virtual float80_t area() const = 0;

  /**
   * Returns the shape's name in lowercase.
   * @return Returns the shape's name in lowercase.
   */
  virtual std::string shape_name() const = 0;

  /**
   * Returns a lowercase string describing what is added when Add is called.
   * @return A lowercase string describing what is added when Add is called.
   */
  virtual std::string add_what() const = 0;

  /**
   * Returns an emtpy instance of the same class as is being called.
   * @return An empty instance of this shape.
   */
  virtual Shape* CreateEmptyDuplicate() const = 0;

  /**
   * Adds two shapes.
   * @param other The second shape to be added
   * @return A new shape resulting from the addition.
   */
  virtual Shape* Add(Shape* other) const = 0;

  /**
   * Prompts the user to enter the details of the shape.
   */
  virtual void PromptShape() = 0;
};
