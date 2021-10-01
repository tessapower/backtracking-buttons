#include "../include/Coord.h"

Coord::Coord(): x{0}, y{0} {}
Coord::Coord(int X, int Y): x{X}, y{Y} {}

std::vector<Coord> Coord::neighbors() {
    // We base the neighboring coordinates on the graphics Cartesian Coordinate
    // system, with the origin starting in the top left.
    // x increases horizontally to the right, y increases vertically down.
    // Neighbours:       [x  , y-1] (Top)
    // (Left) [x-1, y  ] [x  , y  ] [x+1, y  ] (Right)
    //                   [x  , y+1] (Bottom)
    //
    Coord top{x, y - 1};
    Coord bottom{x, y + 1};
    Coord left{x - 1, y};
    Coord right{x + 1, y};

    return std::vector<Coord> {top, right, bottom, left};
}
