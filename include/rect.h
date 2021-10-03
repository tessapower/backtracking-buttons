#ifndef RECT_H
#define RECT_H

#include <vector>

#include "point.h"

class Rect {
public:
    int min_x;
    int max_x;
    int min_y;
    int max_y;

    Rect()
        : min_x{0}, max_x{0}, min_y{0}, max_y{0} {}
    Rect(int min_x, int max_x, int min_y, int max_y)
            : min_x{min_x}, max_x{max_x}, min_y{min_y}, max_y{max_y} {}

    [[nodiscard]] inline int width() const { return max_x - min_x; }
    [[nodiscard]] inline int height() const { return max_y - min_y; }
    [[nodiscard]] Point center() const;
    void expand_to_include(Point const& c);
    [[nodiscard]] std::vector<Point> points_on_perimeter() const;
    [[nodiscard]] bool is_point_on_perimeter(Point const& p) const;
    [[nodiscard]] bool contains_point(Point const& p) const;
};

#endif //RECT_H
