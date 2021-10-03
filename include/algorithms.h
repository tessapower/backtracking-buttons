#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <optional>
#include <string>

#include "button.h"
#include "color.h"
#include "pixel_class.h"
#include "point.h"
#include "rect.h"

// TODO: Mark functions that are noexcept
// TODO: check for const correctness
// TODO: comment functions

void process_image();

std::vector<Button> discover_buttons();

std::optional<Point> next_point(Point current);

bool is_button_color(pixel_class const& px);

bool is_not_button_color(pixel_class const& px);

void discover_bounds(Point const& point, Rect& discovered);

Button assess_button(Rect const& bounds);

pixel_class* get_pixel(Point const& p);

void draw_points(std::vector<Point> const& points, Color const& color);

#endif //ALGORITHMS_H
