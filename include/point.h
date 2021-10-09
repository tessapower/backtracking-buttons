#ifndef POINT_H
#define POINT_H

#include <array>

/**
 * A point on a 2D Cartesian coordinate plane.
 */
class Point {
public:
  /* ========================================================== Constructor */
  constexpr Point(int X, int Y) noexcept : x{X}, y{Y} {};

  /* ===================================================== Member Variables */
  int x;
  int y;

  /* ======================================================== Class Methods */
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
};

#endif // POINT_H
