#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include "point.h"
#include "rect.h"

class Circle {
public:
    Point origin;
    int radius;

    Circle(Point o, int r): origin{o}, radius{r} {};

    [[nodiscard]] std::vector<Point> points_on_circumference() const;
    [[nodiscard]] bool is_point_on_circumference(Point const& p) const;
    [[nodiscard]] Rect bounding_box() const;
    [[nodiscard]] bool contains_point(Point const& p) const;
};

#endif //CIRCLE_H
