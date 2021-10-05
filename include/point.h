#ifndef POINT_H
#define POINT_H

#include <array>

/**
 * A point on a 2D Cartesian coordinate plane.
 */
class Point {
public:
    int x;
    int y;

    Point(int x, int y);

    /**
     * @return Array containing the neighboring top, right, bottom, and left
     *   points as cartesian coordinates in that order.
     */
    [[nodiscard]] std::array<Point, 4> neighbors() const;
    friend bool operator==(const Point& lhs, const Point& rhs);
    friend bool operator!=(const Point& lhs, const Point& rhs);
};

#endif //POINT_H
