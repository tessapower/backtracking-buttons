//
// Created by Tessa Power on 30/09/21.
//

#include "Pixel.h"

// Default constructor
Pixel::Pixel(): R{0}, G{0}, B{0}, was_seen{false} {}

// Constructor
Pixel::Pixel(int r, int g, int b, bool was_seen)
: R{r}, G{g}, B{b}, was_seen{false} {}

void Pixel::set_rgb_values(int r, int g, int b) {
    R = r;
    G = g;
    B = b;
}

std::ostream& operator<<(std::ostream& os, const Pixel& p) {
    os << p.R << " " << p.G << " " << p.B << "  ";

    return os;
}

bool operator==(const Pixel& lhs, const Pixel& rhs) {
    return lhs.red() == rhs.red()
           && lhs.green() == rhs.green()
           && lhs.blue() == rhs.blue();
}

bool operator!=(const Pixel& lhs, const Pixel& rhs) {
    return !(lhs == rhs);
}
