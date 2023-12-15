#ifndef POINT_H
#define POINT_H

#include <array>

namespace geom {
/**
 * A point on a 2D Cartesian coordinate plane.
 */
class Point {
public:
  constexpr Point(int x, int y) noexcept : _x{x}, _y{y} {};

  [[nodiscard]] auto x() const -> int { return _x; }
  [[nodiscard]] auto y() const -> int { return _y; }

  /**
   * @return Array containing the neighboring top, right, bottom, and left
   *   points as cartesian coordinates, in that order.
   */
  [[nodiscard]] auto neighbors() const -> std::array<Point, 4>;

  constexpr friend auto operator==(Point const& lhs, Point const& rhs) -> bool {
    return lhs._x == rhs._x && lhs._y == rhs._y;
  }

  constexpr friend auto operator!=(Point const& lhs, Point const& rhs) -> bool {
    return !(lhs == rhs);
  }

private:
  int _x;
  int _y;
};
} // namespace geom

#endif // POINT_H
