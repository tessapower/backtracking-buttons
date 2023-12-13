// Styleguide: Google C++ Style Guidelines
// https://google.github.io/styleguide/cppguide.html
// C++ Standard: C++17
// clang++ -std=c++17 -o main main.cpp && ./main

#include <cstdlib>

#include <alg/algorithms.h>

const std::string kOutputFilename = "Buttons_processed.ppm";

int main() {
  img::loadButtons();
  alg::process_image();
  img::saveButtons(kOutputFilename);

  return EXIT_SUCCESS;
}
