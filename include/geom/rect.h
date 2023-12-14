#ifndef RECT_H
#define RECT_H

#include <optional>
#include <vector>

#include <geom/point.h>

namespace geom {
class RectIterator;
class PerimeterIterator;

/**
 * A rectangle on a 2D Cartesian coordinate plane.
 */
class Rect {
public:
  explicit Rect(Point p) noexcept
      : min_x{p.x()}, max_x{p.x()}, min_y{p.y()},
        max_y{p.y()} {};

  constexpr Rect(int min_x, int max_x, int min_y, int max_y) noexcept
      : min_x{min_x}, max_x{max_x}, min_y{min_y}, max_y{max_y} {};

  [[nodiscard]] auto get_min_x() const -> int { return min_x; }
  [[nodiscard]] auto get_max_x() const -> int { return max_x; }
  [[nodiscard]] auto get_min_y() const -> int { return min_y; }
  [[nodiscard]] auto get_max_y() const -> int { return max_y; }

  [[nodiscard]] constexpr auto width() const -> int { return max_x - min_x; }
  [[nodiscard]] constexpr auto height() const -> int { return max_y - min_y; }

  [[nodiscard]] auto perimeter() const -> PerimeterIterator;

  [[nodiscard]] auto begin() const -> RectIterator;
  [[nodiscard]] auto end() const -> RectIterator;

  [[nodiscard]] constexpr auto center() const -> Point {
    return Point{(max_x + min_x) / 2, (max_y + min_y) / 2};
  }

  [[nodiscard]] constexpr auto is_fully_enclosed_by(Rect const &other) const
      -> bool {
    return this->min_x > other.min_x &&
           this->max_x<other.max_x &&this->min_y> other.min_y &&
           this->max_y < other.max_y;
  }

  auto expand_to_include(Point const &c) -> void;

private:
  int min_x;
  int max_x;
  int min_y;
  int max_y;
};

/**
 * An iterator which iterates over all points in a rectangle, from top to bottom
 * and left to right.
 */
class RectIterator {
public:
  RectIterator(Rect const &rect, Point starting_point) noexcept
      : rect{rect}, current{starting_point} {};

  [[nodiscard]] auto operator*() const -> const Point & { return current; };

  auto operator++() -> RectIterator;

  friend auto operator!=(RectIterator const &lhs, RectIterator const &rhs)
      -> bool {
    return lhs.current != rhs.current;
  }

  friend Rect;

private:
  Rect rect;
  Point current = Point{rect.get_min_x(), rect.get_min_y()};
};

class PerimeterIterator {
public:
  constexpr PerimeterIterator(Rect const &rect, Point starting_point) noexcept
      : rect{rect}, current{starting_point} {};

  [[nodiscard]] auto operator*() const -> const Point & { return current; };

  auto operator++() -> PerimeterIterator;

  friend auto operator!=(PerimeterIterator const &lhs,
                         PerimeterIterator const &rhs) -> bool {
    return lhs.current != rhs.current;
  }

  [[nodiscard]] auto begin() const -> PerimeterIterator;
  [[nodiscard]] auto end() const -> PerimeterIterator;

private:
  Rect const &rect;
  Point current;
};
} // namespace geom

#endif // RECT_H
