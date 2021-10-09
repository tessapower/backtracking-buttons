#include "rect.h"

RectIterator Rect::begin() const {
    return RectIterator{*this, Point{min_x, min_y}};
}

RectIterator Rect::end() const {
    return RectIterator{*this, Point{min_x, max_y + 1}};
}

PerimeterIterator Rect::perimeter() const {
    return PerimeterIterator{*this, Point{this->min_x, this->min_y}};
}

void Rect::expand_to_include(Point const& c) {
    min_x = std::min(min_x, c.x);
    max_x = std::max(max_x, c.x);
    min_y = std::min(min_y, c.y);
    max_y = std::max(max_y, c.y);
}

RectIterator RectIterator::operator++() {
    if (current.x < rect.max_x) {
        ++current.x;
    } else {
        current.x = rect.min_x;
        ++current.y;
    }

    return *this;
}

PerimeterIterator PerimeterIterator::begin() const {
    return PerimeterIterator{rect, Point{rect.min_x, rect.min_y}};
}

PerimeterIterator PerimeterIterator::end() const {
    return PerimeterIterator{rect, Point{rect.min_x, rect.max_y + 1}};
}

PerimeterIterator PerimeterIterator::operator++() {
    if (current.y == rect.min_y || current.y == rect.max_y) {
        if  (current.x < rect.max_x) {
            ++current.x;
        } else {
            current.x = rect.min_x;
            ++current.y;
        }
    } else {
        if (current.x == rect.min_x) {
            current.x = rect.max_x;
        } else if (current.x == rect.max_x) {
            current.x = rect.min_x;
            ++current.y;
        }
    }

    return *this;
}
