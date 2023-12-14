#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace geom {
class Color {
public:
  /* ========================================================== Constructor ==*/
  constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept
      : R{r}, G{g}, B{b} {};

  /* ===================================================== Member Variables ==*/
  const uint8_t R;
  const uint8_t G;
  const uint8_t B;

  /* ======================================================== Class Methods ==*/
  constexpr static auto Red() -> Color { return Color{255, 0, 0}; }
  constexpr static auto EmeraldGreen() -> Color { return Color{0, 204, 102}; }
  constexpr static auto AzureBlue() -> Color { return Color{0, 127, 255}; }
};
} // namespace geom

#endif // COLOR_H
