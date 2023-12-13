#include "rect.h"

geom::RectIterator geom::Rect::begin() const {
  return RectIterator{*this, Point{min_x, min_y}};
}

geom::RectIterator geom::Rect::end() const {
  return RectIterator{*this, Point{min_x, max_y + 1}};
}

geom::PerimeterIterator geom::Rect::perimeter() const {
  return PerimeterIterator{*this, Point{this->min_x, this->min_y}};
}

void geom::Rect::expand_to_include(Point const &c) {
  min_x = std::min(min_x, c.get_x());
  max_x = std::max(max_x, c.get_x());
  min_y = std::min(min_y, c.get_y());
  max_y = std::max(max_y, c.get_y());
}

geom::RectIterator geom::RectIterator::operator++() {
  if (current.get_x() < rect.get_max_x()) {
    current = Point{current.get_x() + 1, current.get_y()};
  } else {
    current = Point{rect.get_min_x(), current.get_y() + 1};
  }

  return *this;
}

geom::PerimeterIterator geom::PerimeterIterator::begin() const {
  return PerimeterIterator{rect, Point{rect.get_min_x(), rect.get_min_y()}};
}

geom::PerimeterIterator geom::PerimeterIterator::end() const {
  return PerimeterIterator{rect, Point{rect.get_min_x(), rect.get_max_y() + 1}};
}

geom::PerimeterIterator geom::PerimeterIterator::operator++() {
  // Top or bottom edges

  if (current.get_y() == rect.get_min_y() ||
      current.get_y() == rect.get_max_y()) {
    if (current.get_x() < rect.get_max_x()) {
      current = Point{current.get_x() + 1, current.get_y()};
    } else {
      current = Point{rect.get_min_x(), current.get_y() + 1};
    }
  } else {
    // Flip flop between vertical edges
    if (current.get_x() == rect.get_min_x()) {
      current = Point{rect.get_max_x(), current.get_y()};
    } else if (current.get_x() == rect.get_max_x()) {
      current = Point{rect.get_min_x(), current.get_y() + 1};
    }
  }

  return *this;
}