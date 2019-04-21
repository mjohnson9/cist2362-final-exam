// Copyright 2019 Michael Johnson

#include <iostream>
#include <stdexcept>

#include "finalexam/ui.h"

/**
 * The entrypoint for the program.
 * @return The exit code.
 */
int main() {
  try {
    mjohnson::finalexam::Run();
  } catch (const std::exception& ex) {
    std::cerr << "Program terminated with an unhandled exception: "
              << typeid(ex).name() << std::endl
              << ex.what() << std::endl;
    return 1;
  }
  return 0;
}
