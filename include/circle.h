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
  /* ========================================================== Constructor */
  constexpr Circle(Point o, int r) noexcept : origin{o}, radius{r} {};

  /* ===================================================== Member Variables */
  const Point origin;
  const int radius;

  /* ======================================================== Class Methods */
  [[nodiscard]] CircumferenceIterator circumference() const;
  [[nodiscard]] constexpr Rect bounding_box() const {
    return Rect{origin.x - radius, origin.x + radius, origin.y - radius,
                origin.y + radius};
  }
};

class CircumferenceIterator {
public:
  // Include the usual iterator tags for compatability with STL algorithms
  using iterator_category = std::forward_iterator_tag;
  using difference_type = int;
  using value_type = Point;
  using pointer = Point *;
  using reference = Point &;

  /* ========================================================== Constructor */
  constexpr CircumferenceIterator(Circle const &c, int dx) noexcept
      : circle{c}, dx{dx} {};

  /* ======================================================== Class Methods */
  [[nodiscard]] value_type operator*() const;
  CircumferenceIterator operator++();

  friend bool operator==(CircumferenceIterator const &lhs,
                         CircumferenceIterator const &rhs) {
    return lhs.dx == rhs.dx;
  }

  friend bool operator!=(CircumferenceIterator const &lhs,
                         CircumferenceIterator const &rhs) {
    return !(lhs == rhs);
  }

  [[nodiscard]] CircumferenceIterator begin() const;
  [[nodiscard]] CircumferenceIterator end() const;

private:
  Circle const &circle;
  int dx = 0;
  int octant = 0;
};

} // namespace geom

#endif // CIRCLE_H
