#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <optional>
#include <string>

#include "coord.h"
#include "pixel_class.h"
#include "bounds.h"

void process_image();

bool is_button_color(pixel_class const& p);

void discover_bounds(Coord const& coord, Bounds& discovered);

std::vector<Bounds> find_buttons();

pixel_class* get_pixel(Coord const& c);

#endif //ALGORITHMS_H
