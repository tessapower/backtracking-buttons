#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"
#include "rect.h"
#include <cmath>
#include <vector>

namespace geom {
class CircumferenceIterator;

class Circle {
public:
  /* ========================================================== Constructor ==*/
  constexpr Circle(Point o, int r) noexcept : origin{o}, radius{r} {};

  /* ======================================================== Class Methods ==*/
  [[nodiscard]] auto get_origin() const -> Point { return origin; }
  [[nodiscard]] auto get_radius() const -> int { return radius; }

  [[nodiscard]] auto circumference() const -> CircumferenceIterator;
  [[nodiscard]] auto bounding_box() const -> Rect {
    return Rect{origin.x() - radius, origin.x() + radius, origin.y() - radius, origin.y() + radius};
  }

private:
  /* ===================================================== Member Variables ==*/
  const Point origin;
  const int radius;
};

class CircumferenceIterator {
public:
  // Include the usual iterator tags for compatability with STL algorithms
  using iterator_category = std::forward_iterator_tag;
  using difference_type = int;
  using value_type = Point;
  using pointer = Point *;
  using reference = Point &;

  /* ========================================================== Constructor ==*/
  /** @brief Constructs a CircumferenceIterator for the given circle.
   *
   * @param[in] c The circle to iterate over.
   * @param[in] dx The initial x offset from the origin.
   */
  CircumferenceIterator(Circle const& c, int dx) noexcept
      : circle{c}, dx{dx}, radius{c.get_radius()},
        origin_x{c.get_origin().x()}, origin_y{c.get_origin().y()} {};

  /* ======================================================== Class Methods ==*/
  [[nodiscard]] auto operator*() const -> value_type;
  auto operator++() -> CircumferenceIterator;

  friend auto operator==(CircumferenceIterator const& lhs,
                         CircumferenceIterator const& rhs) -> bool {
    return lhs.dx == rhs.dx;
  }

  friend auto operator!=(CircumferenceIterator const& lhs,
                         CircumferenceIterator const& rhs) -> bool {
    return !(lhs == rhs);
  }

  [[nodiscard]] auto begin() const -> CircumferenceIterator;
  [[nodiscard]] auto end() const -> CircumferenceIterator;

private:
  Circle const& circle;
  int const origin_x;
  int const origin_y;
  int const radius;
  int dx = 0;
  int octant = 0;
};
} // namespace geom

#endif // CIRCLE_H
