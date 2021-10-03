#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

class Color {
public:
    const uint8_t R;
    const uint8_t G;
    const uint8_t B;

    Color(uint8_t r, uint8_t g, uint8_t b) noexcept : R{r}, G{g}, B{b} {};
    static Color Red();
    static Color Green();
    static Color LightBlue();
};

#endif //COLOR_H
