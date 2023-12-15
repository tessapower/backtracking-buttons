#include "rect.h"

auto geom::Rect::begin() const -> geom::RectIterator {
  return RectIterator{*this, Point{min_x, min_y}};
}

auto geom::Rect::end() const -> geom::RectIterator {
  return RectIterator{*this, Point{min_x, max_y + 1}};
}

auto geom::Rect::perimeter() const -> geom::PerimeterIterator {
  return PerimeterIterator{*this, Point{this->min_x, this->min_y}};
}

auto geom::Rect::expand_to_include(Point const& c) -> void {
  min_x = std::min(min_x, c.x());
  max_x = std::max(max_x, c.x());
  min_y = std::min(min_y, c.y());
  max_y = std::max(max_y, c.y());
}

auto geom::RectIterator::operator++() -> geom::RectIterator {
  if (current.x() < rect.get_max_x()) {
    current = Point{current.x() + 1, current.y()};
  } else {
    current = Point{rect.get_min_x(), current.y() + 1};
  }

  return *this;
}

auto geom::PerimeterIterator::begin() const -> geom::PerimeterIterator {
  return PerimeterIterator{rect, Point{rect.get_min_x(), rect.get_min_y()}};
}

auto geom::PerimeterIterator::end() const -> geom::PerimeterIterator {
  return PerimeterIterator{rect, Point{rect.get_min_x(), rect.get_max_y() + 1}};
}

auto geom::PerimeterIterator::operator++() -> geom::PerimeterIterator {
  // Top or bottom edges
  if (current.y() == rect.get_min_y() || current.y() == rect.get_max_y()) {
    if (current.x() < rect.get_max_x()) {
      current = Point{current.x() + 1, current.y()};
    } else {
      current = Point{rect.get_min_x(), current.y() + 1};
    }
  } else {
    // Flip flop between vertical edges
    if (current.x() == rect.get_min_x()) {
      current = Point{rect.get_max_x(), current.y()};
    } else if (current.x() == rect.get_max_x()) {
      current = Point{rect.get_min_x(), current.y() + 1};
    }
  }

  return *this;
}
