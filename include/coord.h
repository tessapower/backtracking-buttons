#ifndef COORD_H
#define COORD_H

#include <vector>

// 2D cartesian coordinate
class Coord {
public:
    int x;
    int y;

    Coord();
    Coord(int x, int y);

    /**
     * @return Vector containing the neighboring top, right, bottom, and left
     *   coordinates in that order.
     */
    [[nodiscard]] std::vector<Coord> neighbors() const;
};

#endif //COORD_H
