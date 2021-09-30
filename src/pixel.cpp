//
// Created by Tessa Power on 30/09/21.
//

#include "../include/pixel.h"

// Default constructor
Pixel::Pixel(): R{0}, G{0}, B{0}, seen = false {}

// Constructor
Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, bool seen)
: R{r}, G{g}, B{b}, seen = false {

}

void Pixel::set_rgb_value(uint8_t r, uint8_t g, uint8_t b) {
    R = r;
    G = g;
    B = b;
}

std::ostream& operator<<(std::ostream& os, const Pixel& p) {
    os << R << " " << G << " " << B << "  ";

    return os;
}

bool operator==(const Pixel& lhs, const Pixel& rhs) const {
    return lhs.R() == rhs.R()
           && lhs.G() == rhs.G()
           && lhs.B() == rhs.B();
}

bool operator!=(const Pixel& lhs, const Pixel& rhs) const {
    return !(lhs == rhs);
}
