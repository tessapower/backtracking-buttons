#ifndef SCAN_H
#define SCAN_H

#include <geom/point.h>
#include <img/pixel.h>
#include <string>
#include <vector>

namespace img {
class Scan {
public:
  explicit Scan(std::string const& input_filename) {
    // Default values
    _screen_x = 0;
    _screen_y = 0;
    _max_colors = 0;

    load_ppm_file(input_filename);
  }

  [[nodiscard]] auto get_pixel(geom::Point const& point) const
      -> MaybeConstPixel;
  [[nodiscard]] auto get_pixel(geom::Point const& point)
      -> MaybePixel;

  /**
   * Saves the scan to a PPM file with the given filename.
   * @param output_filename
   */
  auto save_ppm_file(std::string const& output_filename) const -> void;

  /**
   * @return The width of the image in pixels.
   */
  [[nodiscard]] auto screen_x() const -> int { return _screen_x; }

  /**
   * @return The height of the image in pixels.
   */
  [[nodiscard]] auto screen_y() const -> int { return _screen_y; }

private:
  auto load_ppm_file(std::string const& input_filename) -> void;

  std::vector<std::vector<img::Pixel>> _pixel_data;
  int _screen_x;
  int _screen_y;
  int _max_colors;
};
} // namespace img

#endif // SCAN_H
