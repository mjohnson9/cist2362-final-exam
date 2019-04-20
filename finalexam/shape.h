// Copyright 2019 Michael Johnson

#pragma once

class Shape {
 public:
  virtual Shape* Add(Shape*, Shape*) = 0;
  virtual double GetArea() = 0;
};
