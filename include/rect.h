#ifndef RECT_H
#define RECT_H

#include <vector>
#include <optional>

#include "point.h"

class RectIterator;

class Rect {
public:
    /* ========================================================= Constructors */
    constexpr explicit Rect(Point p):
        min_x{p.x}, max_x{p.x}, min_y{p.y}, max_y{p.y} {};

    constexpr Rect(int min_x, int max_x, int min_y, int max_y):
        min_x{min_x}, max_x{max_x}, min_y{min_y}, max_y{max_y} {};

    /* ===================================================== Member Variables */
    int min_x;
    int max_x;
    int min_y;
    int max_y;

    /* ======================================================== Class Methods */

    [[nodiscard]] constexpr int width() const { return max_x - min_x; }
    [[nodiscard]] constexpr int height() const { return max_y - min_y; }

    [[nodiscard]] RectIterator begin() const;
    [[nodiscard]] RectIterator end() const;

    [[nodiscard]] constexpr Point center() const {
        return Point{(max_x + min_x)/2, (max_y + min_y)/2};
    }

    [[nodiscard]] std::vector<Point> points_on_perimeter() const;
    // TODO: Rename new better cheryl name
    [[nodiscard]] bool is_proper_subset_of(Rect const& other) const;

    void expand_to_include(Point const& c);
};

class RectIterator {
public:
    /* ========================================================== Constructor */
    RectIterator(Rect const& rect, Point starting_point):
        rect{rect}, current{starting_point} {};

    /* ======================================================== Class Methods */
    [[nodiscard]] constexpr Point const& operator*() const {
        return current;
    };

    RectIterator operator++();

    friend constexpr bool operator!=(RectIterator const& lhs, RectIterator const& rhs) {
        return lhs.current != rhs.current;
    }

    friend Rect;

private:
    Rect rect;
    Point current = Point{rect.min_x, rect.min_y};
};

#endif //RECT_H
