#include "circle.h"
#include <cassert>

auto geom::Circle::circumference() const -> geom::CircumferenceIterator {
  return geom::CircumferenceIterator{*this, 0};
}

auto geom::CircumferenceIterator::begin() const -> geom::CircumferenceIterator {
  return geom::CircumferenceIterator{circle, 0};
}

auto geom::CircumferenceIterator::end() const -> geom::CircumferenceIterator {
  const int end_dx = static_cast<int>(circle.get_radius() / sqrt(2) + 1);

  return geom::CircumferenceIterator{circle, end_dx};
}

auto geom::CircumferenceIterator::operator*() const -> geom::Point {
  const int dy = static_cast<int>(sqrt(pow(radius, 2) - pow(dx, 2)));

  switch (octant) {
  case 0: return Point{origin_x + dx, origin_y + dy};
  case 1: return Point{origin_x + dx, origin_y - dy};
  case 2: return Point{origin_x - dx, origin_y + dy};
  case 3: return Point{origin_x - dx, origin_y - dy};
  case 4: return Point{origin_x + dy, origin_y + dx};
  case 5: return Point{origin_x + dy, origin_y - dx};
  case 6: return Point{origin_x - dy, origin_y + dx};
  case 7: return Point{origin_x - dy, origin_y - dx};
  default: assert(false); // Impossible situation
  }

  return {0, 0};
}

auto geom::CircumferenceIterator::operator++() -> geom::CircumferenceIterator {
  if ((++octant %= 8) == 0) ++dx;

  return *this;
}
