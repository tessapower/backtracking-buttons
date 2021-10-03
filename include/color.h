#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

class Color {
public:
    const uint8_t R;
    const uint8_t G;
    const uint8_t B;

    Color(uint8_t r, uint8_t g, uint8_t b) noexcept : R{r}, G{g}, B{b} {};
};

const Color kColorGreen{0, 255, 0};
const Color kColorRed{255, 0, 0};
const Color kColorBlack{0, 0, 0};

#endif //COLOR_H
