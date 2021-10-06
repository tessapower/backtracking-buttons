#ifndef RECT_H
#define RECT_H

#include <vector>
#include <optional>

#include "point.h"

class RectIterator;

class Rect {
public:
    /* ========================================================= Constructors */
    Rect(const Rect&) = default;
    Rect(): min_x{0}, max_x{0}, min_y{0}, max_y{0} {};
    explicit Rect(Point p): min_x{p.x}, max_x{p.x}, min_y{p.y}, max_y{p.y} {};
    Rect(int min_x, int max_x, int min_y, int max_y)
            : min_x{min_x}, max_x{max_x}, min_y{min_y}, max_y{max_y} {};

    /* ===================================================== Member Variables */
    int min_x;
    int max_x;
    int min_y;
    int max_y;

    /* ======================================================== Class Methods */

    [[nodiscard]] inline int width() const { return max_x - min_x; }
    [[nodiscard]] inline int height() const { return max_y - min_y; }

    [[nodiscard]] RectIterator begin() const;
    [[nodiscard]] RectIterator end() const;

    [[nodiscard]] Point center() const;
    void expand_to_include(Point const& c);
    [[nodiscard]] std::vector<Point> points_on_perimeter() const;
    [[nodiscard]] bool is_point_on_perimeter(Point const& p) const;
    [[nodiscard]] bool contains_point(Point const& p) const;
    [[nodiscard]] bool is_proper_subset_of(Rect const& bounds) const;
};

class RectIterator {
public:
    /* ========================================================== Constructor */
    RectIterator(Rect const& rect, Point starting_point)
        : rect{rect}, current{starting_point} {};

    /* ======================================================== Class Methods */
    [[nodiscard]] Point const& operator*() const { return current; };
    RectIterator operator++();
    friend bool operator!=(RectIterator const& lhs, RectIterator const& rhs);

    friend Rect;

private:
    /* ================================================== Private Constructor */
    explicit RectIterator(Rect const& rect): rect{rect} {};

    /* ============================================= Private Member Variables */
    Rect rect;
    Point current = Point{rect.min_x, rect.min_y};
};

#endif //RECT_H
