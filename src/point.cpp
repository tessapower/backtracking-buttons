#include <array>
#include "point.h"

Point::Point(): x{0}, y{0} {}
Point::Point(int X, int Y): x{X}, y{Y} {}

std::array<Point, 4> Point::neighbors() const {
    // We base the neighboring points on the graphics Cartesian Coordinate system
    // with the origin starting in the top left corner [0, 0].
    // x increases horizontally to the right, y increases vertically down.
    // Neighbours:       [x  , y-1] (Top)
    // (Left) [x-1, y  ] [x  , y  ] [x+1, y  ] (Right)
    //                   [x  , y+1] (Bottom)
    //
    Point top{x, y - 1};
    Point bottom{x, y + 1};
    Point left{x - 1, y};
    Point right{x + 1, y};

    return std::array<Point, 4>{top, right, bottom, left};
}
