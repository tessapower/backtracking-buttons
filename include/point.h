#ifndef POINT_H
#define POINT_H

#include <array>

namespace geom {

/**
 * A point on a 2D Cartesian coordinate plane.
 */
class Point {
public:
  /* ========================================================== Constructor */
  constexpr Point(int X, int Y) noexcept : x{X}, y{Y} {};

  /* ======================================================== Class Methods */
  [[nodiscard]] int get_x() const { return x; }
  [[nodiscard]] int get_y() const { return y; }

  /**
   * @return Array containing the neighboring top, right, bottom, and left
   *   points as cartesian coordinates in that order.
   */
  [[nodiscard]] std::array<Point, 4> neighbors() const;

  constexpr friend bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  constexpr friend bool operator!=(const Point &lhs, const Point &rhs) {
    return !(lhs == rhs);
  }

private:
  /* ===================================================== Member Variables */
  int x;
  int y;
};

} // namespace geom

#endif // POINT_H
