//
// Created by Tessa Power on 1/10/21.
//

#include <cmath>
#include "circle.h"

[[nodiscard]] std::vector<Coord> Circle::points_on_circumference() const {
    std::vector<Coord> points;
    for (int dx = 0; dx <= radius/sqrt(2) ; dx++) {
        const int dy = (int)sqrt(pow(radius, 2) - pow(dx, 2));
        points.emplace_back(origin.x + dx, origin.y + dy);
        points.emplace_back(origin.x + dx, origin.y - dy);
        points.emplace_back(origin.x - dx, origin.y + dy);
        points.emplace_back(origin.x - dx, origin.y - dy);
        points.emplace_back(origin.x + dy, origin.y + dx);
        points.emplace_back(origin.x + dy, origin.y - dx);
        points.emplace_back(origin.x - dy, origin.y + dx);
        points.emplace_back(origin.x - dy, origin.y - dx);
    }

    return points;
}


