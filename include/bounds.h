#ifndef BOUNDS_H
#define BOUNDS_H

#include "coord.h"

class Bounds {
public:
    Bounds();
    Bounds(Coord coord);
    int min_x, max_x, min_y, max_y;
    inline const int width() const { return max_x - min_x; }
    inline const int height() const { return max_y - min_y; }
    void expand_to_include(Coord const& c);
};

//class Circle {
//public:
//    Coord origin;
//    int radius;
//    std::vector<Coord> points_on_circumference() const;
//};

#endif //BOUNDS_H
