#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <optional>
#include <string>
#include <vector>

#include "circle.h"
#include "color.h"
#include "pixel_class.h"
#include "point.h"
#include "rect.h"

// TODO: Mark functions that are noexcept
// TODO: check for const correctness
// TODO: comment functions

void process_image();

std::vector<Rect> discover_all_button_bounds();

bool discover_extent_of_connected_points(Point const& point, Rect const& bounds,
                                         std::optional<std::vector<Point>> &visited);

pixel_class* get_pixel(Point const& p);

void discover_bounds(Point const& point, Rect& discovered);

bool is_part_of_button(Point const& point);

int num_enclosed_button_holes(Rect const& bounds);

void draw_points(std::vector<Point> const& points, Color const& color);

#endif //ALGORITHMS_H
