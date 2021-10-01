#include "bounds.h"

void Bounds::expand_to_include(Coord const& c) {
    min_x = std::min(min_x, c.x);
    max_x = std::max(max_x, c.x);
    min_y = std::min(min_y, c.y);
    max_y = std::max(max_y, c.y);
}

std::vector<Coord> Bounds::points_on_bounds() const {
    std::vector<Coord> points;
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

[[nodiscard]] Coord Bounds::center() const {
    const int x = (max_x + min_x)/2;
    const int y = (max_y + min_y)/2;

    return Coord{x, y};
}
