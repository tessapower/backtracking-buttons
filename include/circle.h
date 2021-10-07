#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include "point.h"
#include "rect.h"

class Circle {
public:
    /* ========================================================== Constructor */
    Circle(Point o, int r): origin{o}, radius{r} {};

    /* ===================================================== Member Variables */
    const Point origin;
    const int radius;

    /* ======================================================== Class Methods */
    [[nodiscard]] std::vector<Point> points_on_circumference() const;
    [[nodiscard]] Rect bounding_box() const;
};

#endif //CIRCLE_H
