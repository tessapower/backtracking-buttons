#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <optional>
#include <string>

#include "bounds.h"
#include "color.h"
#include "coord.h"
#include "pixel_class.h"

void process_image();

bool is_button_color(pixel_class const& p);

void discover_bounds(Coord const& coord, Bounds& discovered);

std::vector<Bounds> find_buttons();

pixel_class* get_pixel(Coord const& c);

void draw_bounding_box(Bounds const& bounds, Color const& color);

#endif //ALGORITHMS_H
