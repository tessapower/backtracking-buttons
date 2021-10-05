//
// Created by Tessa Power on 1/10/21.
//

#include <cmath>
#include "circle.h"

[[nodiscard]] std::vector<Point> Circle::points_on_circumference() const {
    std::vector<Point> points;
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

[[nodiscard]] bool Circle::is_point_on_circumference(Point const& p) const {
    return pow(origin.x - p.x, 2) + pow(origin.y - p.y, 2) == pow(radius, 2);
}

Rect Circle::bounding_box() const {
    return Rect{origin.x - radius, origin.x + radius,
                origin.y - radius, origin.y + radius};
}

bool Circle::contains_point(Point const& p) const {
    return pow(origin.x - p.x, 2) + pow(origin.y - p.y, 2) <= pow(radius, 2);
}


