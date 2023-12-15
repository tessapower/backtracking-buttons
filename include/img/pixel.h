#ifndef PIXEL_H
#define PIXEL_H

#include <geom/color.h>
#include <ostream>

namespace img {
/**
 * @brief Represents a pixel in a scan.
 */
class Pixel {
private:
  int _red;
  int _green;
  int _blue;
  bool _visited;

public:
  Pixel() : _red{0}, _green{0}, _blue{0}, _visited{false} {};
  Pixel(int red, int green, int blue)
      : _red{red}, _green{green}, _blue{blue}, _visited{false} {};

  /**
   * @brief The red component of this pixel.
   */
  [[nodiscard]] auto red() const noexcept -> int { return _red; }

  /**
   * @brief The green component of this pixel.
   */
  [[nodiscard]] auto green() const noexcept -> int {
    return _green;
  }

  /**
   * @brief The blue component of this pixel.
   */
  [[nodiscard]] auto blue() const noexcept -> int {
    return _blue;
  }

  /**
   * @brief Changes the color of this pixel to the given color.
   */
  auto change_color(geom::Color const& color) noexcept -> void {
    _red = color.R;
    _green = color.G;
    _blue = color.B;
  }

  /**
   * @brief Sets whether this pixel has been visited.
   */
  auto visited(bool is_visited) noexcept -> void { _visited = is_visited; }

  /**
   * @brief Returns whether this pixel has been visited.
   */
  [[nodiscard]] auto visited() const noexcept -> bool { return _visited; }

  friend auto operator<<(std::ostream& os, Pixel const& p) -> std::ostream& {
    os << p._red << " " << p._green << " " << p._blue << " ";

    return os;
  }
};

} // namespace img
#endif // PIXEL_H
