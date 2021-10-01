#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include "coord.h"

class Circle {
public:
    Coord origin;
    int radius;

    Circle(Coord o, int r): origin{o},  radius{r} {};

    [[nodiscard]] std::vector<Coord> points_on_circumference() const;
};

#endif //CIRCLE_H
