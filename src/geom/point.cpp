#include "point.h"
#include <array>

auto geom::Point::neighbors() const -> std::array<geom::Point, 4> {
  // We base the neighboring points on the graphics Cartesian Coordinate system
  // with the origin starting in the top left corner [0, 0].
  // x increases horizontally to the right, y increases vertically down.
  // Neighbours:       [x  , y-1] (Top)
  // (Left) [x-1, y  ] [x  , y  ] [x+1, y  ] (Right)
  //                   [x  , y+1] (Bottom)
  //
  Point top{_x, _y - 1};
  Point right{_x + 1, _y};
  Point bottom{_x, _y + 1};
  Point left{_x - 1, _y};

  return std::array<Point, 4>{top, right, bottom, left};
}
