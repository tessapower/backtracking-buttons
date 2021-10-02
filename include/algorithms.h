#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <optional>
#include <string>

#include "bounds.h"
#include "button.h"
#include "color.h"
#include "coord.h"
#include "pixel_class.h"

void process_image();

std::optional<Coord> next_coord(Coord current);

bool is_button_color(pixel_class const& p);

void discover_bounds(Coord const& coord, Bounds& discovered);

std::vector<Bounds> find_buttons();

std::vector<Button> assess_buttons(std::vector<Bounds> const& b);

pixel_class* get_pixel(Coord const& c);

void draw_points(std::vector<Coord> const& coords, Color const& color);

#endif //ALGORITHMS_H