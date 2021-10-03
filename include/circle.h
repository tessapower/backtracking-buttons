#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include "point.h"

class Circle {
public:
    Point origin;
    int radius;

    Circle(Point o, int r): origin{o}, radius{r} {};

    [[nodiscard]] std::vector<Point> points_on_circumference() const;
};

#endif //CIRCLE_H
