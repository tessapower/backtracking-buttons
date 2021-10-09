// Styleguide: Google C++ Style Guidelines
// https://google.github.io/styleguide/cppguide.html
// C++ Standard: C++17
// clang++ -std=c++17 -o main main.cpp && ./main

#include <cstdlib>

#include "algorithms.h"
#include "img.h"

#define OUTPUT_FILE "Buttons_processed.ppm"

int main() {
  img::loadButtons();
  alg::process_image();
  img::saveButtons(OUTPUT_FILE);

  return EXIT_SUCCESS;
}
