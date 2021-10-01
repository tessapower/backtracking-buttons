#ifndef BUTTON_UTILS_H
#define BUTTON_UTILS_H

#include <optional>
#include <string>

#include "Coord.h"
#include "pixel_class.h"
#include "Bounds.h"

void process_image();

bool is_button_color(pixel_class const& p);

void discover_bounds(Coord const& coord, Bounds& discovered);

std::vector<Bounds> find_buttons();

pixel_class* get_pixel(Coord const& c);

#endif //BUTTON_UTILS_H
