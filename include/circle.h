#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>
#include <vector>
#include "point.h"
#include "rect.h"

class CircumferenceIterator;

class Circle {
public:
    /* ========================================================== Constructor */
    Circle(Point o, int r): origin{o}, radius{r} {};

    /* ===================================================== Member Variables */
    const Point origin;
    const int radius;

    /* ======================================================== Class Methods */
    [[nodiscard]] CircumferenceIterator circumference() const;
    [[nodiscard]] Rect bounding_box() const;
};

class CircumferenceIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = int;
    using value_type        = Point;
    using pointer           = Point*;
    using reference         = Point&;

    /* ========================================================== Constructor */
    CircumferenceIterator(Circle const& c, int dx): circle{c}, dx{dx} {};

    /* ======================================================== Class Methods */
    [[nodiscard]] value_type operator*() const;
    CircumferenceIterator operator++();
    friend bool operator==(CircumferenceIterator const& lhs, CircumferenceIterator const& rhs);
    friend bool operator!=(CircumferenceIterator const& lhs, CircumferenceIterator const& rhs);
    [[nodiscard]] CircumferenceIterator begin() const;
    [[nodiscard]] CircumferenceIterator end() const;

private:
    Circle circle;
    int dx = 0;
    int octant = 0;
};

#endif //CIRCLE_H
