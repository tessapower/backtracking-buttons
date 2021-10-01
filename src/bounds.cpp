#include "bounds.h"

Bounds::Bounds()
    : min_x{0}, max_x{0}, min_y{0}, max_y{0} {}

Bounds::Bounds(Coord coord)
    : min_x{coord.x}, max_x{coord.x}, min_y{coord.y}, max_y{coord.y} {}

void Bounds::expand_to_include(Coord const& c) {
    min_x = std::min(min_x, c.x);
    max_x = std::max(max_x, c.x);
    min_y = std::min(min_y, c.y);
    max_y = std::max(max_y, c.y);
}
