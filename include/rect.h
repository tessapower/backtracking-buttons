#ifndef RECT_H
#define RECT_H

#include <vector>
#include <optional>

#include "point.h"

class RectIterator;
class PerimeterIterator;

class Rect {
public:
    /* ========================================================= Constructors */
    constexpr explicit Rect(Point p) noexcept:
        min_x{p.x}, max_x{p.x}, min_y{p.y}, max_y{p.y} {};

    constexpr Rect(int min_x, int max_x, int min_y, int max_y) noexcept:
        min_x{min_x}, max_x{max_x}, min_y{min_y}, max_y{max_y} {};

    /* ===================================================== Member Variables */
    int min_x;
    int max_x;
    int min_y;
    int max_y;

    /* ======================================================== Class Methods */
    [[nodiscard]] constexpr int width() const { return max_x - min_x; }
    [[nodiscard]] constexpr int height() const { return max_y - min_y; }

    [[nodiscard]] PerimeterIterator perimeter() const;

    [[nodiscard]] RectIterator begin() const;
    [[nodiscard]] RectIterator end() const;

    [[nodiscard]] constexpr Point center() const {
        return Point{(max_x + min_x)/2, (max_y + min_y)/2};
    }

    [[nodiscard]] constexpr bool is_fully_enclosed_by(Rect const& other) const {
        return this->min_x > other.min_x &&
               this->max_x < other.max_x &&
               this->min_y > other.min_y &&
               this->max_y < other.max_y;
    }

    void expand_to_include(Point const& c);
};

class RectIterator {
public:
    /* ========================================================== Constructor */
    RectIterator(Rect const& rect, Point starting_point) noexcept:
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

class PerimeterIterator {
public:
    /* ========================================================== Constructor */
    constexpr PerimeterIterator(Rect const& rect, Point starting_point) noexcept:
        rect{rect}, current{starting_point} {};

    /* ======================================================== Class Methods */
    [[nodiscard]] constexpr Point const& operator*() const {
        return current;
    };

    PerimeterIterator operator++();

    friend constexpr bool operator!=(PerimeterIterator const& lhs,
                                     PerimeterIterator const& rhs) {
        return lhs.current != rhs.current;
    }

    [[nodiscard]] PerimeterIterator begin() const;
    [[nodiscard]] PerimeterIterator end() const;

private:
    Rect rect;
    Point current;
};

#endif //RECT_H
