#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <optional>
#include <string>
#include <vector>

#include "button.h"
#include "circle.h"
#include "color.h"
#include "pixel_class.h"
#include "point.h"
#include "rect.h"

// TODO: Mark functions that are noexcept
// TODO: check for const correctness
// TODO: comment functions

void process_image();

std::vector<Button> create_buttons(std::vector<Rect> const& button_bounds);

std::vector<Rect> discover_all_button_bounds();

bool discover_extent_of_connected_points(Point const& point, Rect const& bounds,
                                         std::optional<std::vector<Point>> &visited);

pixel_class* get_pixel(Point const& p);

void discover_bounds(Point const& point, Rect& discovered);

bool is_button_color(pixel_class const& px);

bool is_not_button_color(pixel_class const& px);

int num_enclosed_button_holes(Rect const& bounds);

bool do_any_match(std::vector<Point> const& points,
                  bool (*predicate_fn)(pixel_class const& p));

void draw_points(std::vector<Point> const& points, Color const& color);

#endif //ALGORITHMS_H
