#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

class Color {
public:
    /* ========================================================== Constructor */
    constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept: R{r}, G{g}, B{b} {};

    /* ===================================================== Member Variables */
    const uint8_t R;
    const uint8_t G;
    const uint8_t B;

    /* ======================================================== Class Methods */
    constexpr static Color Red() { return Color{255, 0, 0}; }
    constexpr static Color EmeraldGreen() { return Color{0, 204, 102}; }
    constexpr static Color AzureBlue() { return Color{0, 127, 255}; }
};

#endif //COLOR_H
