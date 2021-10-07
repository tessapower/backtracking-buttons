#include "rect.h"

RectIterator Rect::begin() const {
    return RectIterator{*this, Point{min_x, min_y}};
}

RectIterator Rect::end() const {
    return RectIterator{*this, Point{min_x, max_y+1}};
}

[[nodiscard]] Point Rect::center() const {
    const int x = (max_x + min_x)/2;
    const int y = (max_y + min_y)/2;

    return Point{x, y};
}

void Rect::expand_to_include(Point const& c) {
    min_x = std::min(min_x, c.x);
    max_x = std::max(max_x, c.x);
    min_y = std::min(min_y, c.y);
    max_y = std::max(max_y, c.y);
}

std::vector<Point> Rect::points_on_perimeter() const {
    std::vector<Point> points;
    // Top and bottom
    for (int x = min_x; x < max_x; ++x) {
        points.emplace_back(x, min_y);
        points.emplace_back(x, max_y);
    }

    // Left and right
    for (int y = min_y; y < max_y; ++y) {
        points.emplace_back(min_x, y);
        points.emplace_back(max_x, y);
    }

    return points;
}

bool Rect::is_proper_subset_of(Rect const& other) const {
    return this->min_x > other.min_x &&
           this->max_x < other.max_x &&
           this->min_y > other.min_y &&
           this->max_y < other.max_y;
}

RectIterator RectIterator::operator++() {
    if (current.x < rect.max_x) {
        current.x++;
    } else {
        current.x = rect.min_x;
        current.y++;
    }

    return *this;
}

bool operator!=(RectIterator const& lhs, RectIterator const& rhs) {
    return lhs.current != rhs.current;
}
