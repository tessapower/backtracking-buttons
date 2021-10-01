#ifndef COORD_H
#define COORD_H

#include <vector>

// 2D cartesian coordinate
class Coord {
public:
    Coord();
    Coord(int x, int y);

    /**
     * @return Vector containing the neighboring top, right, bottom, and left
     *   coordinates in that order.
     */
    std::vector<Coord> neighbors();
    int x;
    int y;
};

#endif //COORD_H
