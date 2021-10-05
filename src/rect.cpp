#include "rect.h"

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

[[nodiscard]] Point Rect::center() const {
    const int x = (max_x + min_x)/2;
    const int y = (max_y + min_y)/2;

    return Point{x, y};
}

bool Rect::is_point_on_perimeter(Point const& p) const {
    return p.x == min_x || p.x == max_x || p.y == min_y || p.y == max_y;
}

bool Rect::contains_point(Point const& p) const {
    return p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y;
}


RectIterator Rect::begin() const {
    return RectIterator{*this};
}


RectIterator Rect::end() const {
    return RectIterator{*this, Point{min_x, max_y+1}};
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
