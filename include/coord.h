#ifndef COORD_H
#define COORD_H

#include <array>

// 2D cartesian coordinate
class Coord {
public:
    int x;
    int y;

    Coord();
    Coord(int x, int y);

    /**
     * @return Array containing the neighboring top, right, bottom, and left
     *   coordinates in that order.
     */
    [[nodiscard]] std::array<Coord, 4> neighbors() const;
};

#endif //COORD_H
