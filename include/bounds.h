#ifndef BOUNDS_H
#define BOUNDS_H

#include <vector>

#include "coord.h"

class Bounds {
public:
    int min_x;
    int max_x;
    int min_y;
    int max_y;

    Bounds()
        : min_x{0}, max_x{0}, min_y{0}, max_y{0} {}
    Bounds(int min_x, int max_x, int min_y, int max_y)
            : min_x{min_x}, max_x{max_x}, min_y{min_y}, max_y{max_y} {}

    [[nodiscard]] inline int width() const { return max_x - min_x; }
    [[nodiscard]] inline int height() const { return max_y - min_y; }
    [[nodiscard]] Coord center() const;
    void expand_to_include(Coord const& c);
    [[nodiscard]] std::vector<Coord> points_on_perimeter() const;
};

#endif //BOUNDS_H
