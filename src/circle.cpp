//
// Created by Tessa Power on 1/10/21.
//

#include <cassert>
#include "circle.h"

CircumferenceIterator Circle::circumference() const {
    return CircumferenceIterator{*this, 0};
}

Rect Circle::bounding_box() const {
    return Rect{origin.x - radius, origin.x + radius,
                origin.y - radius, origin.y + radius};
}

CircumferenceIterator CircumferenceIterator::begin() const {
    return CircumferenceIterator{circle, 0};
}

CircumferenceIterator CircumferenceIterator::end() const {
    const int dx = (int)circle.radius/sqrt(2) + 1;
    return CircumferenceIterator{circle, dx};
}

Point CircumferenceIterator::operator*() const {
    const int r = circle.radius;
    const int dy = (int)sqrt(pow(r, 2) - pow(dx, 2));

    Point const& origin = circle.origin;
    switch(octant) {
        case 0: return Point{origin.x + dx, origin.y + dy};
        case 1: return Point{origin.x + dx, origin.y - dy};
        case 2: return Point{origin.x - dx, origin.y + dy};
        case 3: return Point{origin.x - dx, origin.y - dy};
        case 4: return Point{origin.x + dy, origin.y + dx};
        case 5: return Point{origin.x + dy, origin.y - dx};
        case 6: return Point{origin.x - dy, origin.y + dx};
        case 7: return Point{origin.x - dy, origin.y - dx};
        default: assert(false);
    }
}

CircumferenceIterator CircumferenceIterator::operator++() {
    if ((++octant %= 8) == 0) {
        ++dx;
    }

    return *this;
}

bool operator==(CircumferenceIterator const& lhs, CircumferenceIterator const& rhs) {
    return lhs.dx == rhs.dx;
}

bool operator!=(CircumferenceIterator const& lhs, CircumferenceIterator const& rhs) {
    return !(lhs == rhs);
}
