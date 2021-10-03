#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <optional>
#include <string>

#include "rect.h"
#include "button.h"
#include "color.h"
#include "coord.h"
#include "pixel_class.h"

// TODO: Mark functions that are noexcept
// TODO: check for const correctness
// TODO: comment functions

void process_image();

std::optional<Coord> next_coord(Coord current);

bool is_button_color(pixel_class const& p);

bool is_not_button_color(pixel_class const& p);

void discover_bounds(Coord const& coord, Rect& discovered);

std::vector<Rect> discover_button_bounds();

std::vector<Button> assess_buttons(std::vector<Rect> const& b);

pixel_class* get_pixel(Coord const& c);

void draw_points(std::vector<Coord> const& coords, Color const& color);

#endif //ALGORITHMS_H
