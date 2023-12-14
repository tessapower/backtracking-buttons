#include "img/scan.h"
#include <fstream>
#include <sstream>

auto img::Scan::get_pixel(geom::Point const& point) const -> img::Pixel const
    & {
  int x = point.x();
  int y = point.y();
  if (x >= 0 && x < _screen_x && y >= 0 && y < _screen_y) {
    return _pixel_data[y][x];
  }

  throw std::runtime_error("Pixel out of bounds");
}

auto img::Scan::load_ppm_file(const std::string &input_filename) -> void {
  std::fstream input_file;
  std::string line;
  input_file.open(input_filename.c_str(), std::fstream::in);
  if (!input_file.is_open()) {
    throw std::runtime_error("Unable to open file" + input_filename);
  }

  // Read the header
  std::getline(input_file, line); // Corresponds to "P3"
  std::getline(input_file, line); // Corresponds to "# filename"
  input_file >> _screen_x >> _screen_y;
  input_file >> _max_colors;

  // Resize the pixel data, which we will also do for each row
  _pixel_data.resize(_screen_y);
  // Read the pixel data
  for (int y = 0; y < _screen_y; ++y) {
    for (int x = 0; x < _screen_x; ++x) {
      int R, G, B;
      input_file >> R >> G >> B;
      _pixel_data[y].emplace_back(R, G, B);
    }
  }

  input_file.close();
}

auto img::Scan::save_ppm_file(const std::string &output_filename) const
    -> void {
  std::fstream output_file;

  std::cout << "Writing to " << output_filename << std::endl;
  output_file.open(output_filename.c_str(), std::fstream::out);
  if (!output_file.is_open()) {
    throw std::runtime_error("Unable to write to " + output_filename);
  }

  // Needed for .ppm file formatting
  output_file << "P3" << std::endl
              << "# " << output_filename << std::endl
              << _screen_x << " " << _screen_y << std::endl
              << _max_colors << std::endl;

  // pixel rgb values
  for (int y = 0; y < _screen_y; ++y) {
    for (int x = 0; x < _screen_x; ++x) {
      output_file << _pixel_data[y][x];
    }
    output_file << std::endl;
  }

  output_file.close();
}
