// Styleguide: Google C++ Style Guidelines
// https://google.github.io/styleguide/cppguide.html

#include <cstdlib>

#include <alg/algorithms.h>
#include <img/scan.h>

const std::string kInputFilename = PPM_FILES + std::string{"buttons.ppm"};
const std::string kOutputFilename =
    PPM_FILES + std::string{"buttons_processed.ppm"};

auto main() -> int {
  auto scan = img::Scan{kInputFilename};
  auto processed_scan = alg::process_scan(scan);
  processed_scan.save_ppm_file(kOutputFilename);

  return EXIT_SUCCESS;
}
