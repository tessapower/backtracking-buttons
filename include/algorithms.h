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

std::optional<Point> next_point_in_rect(std::optional<Point> &point, Rect const& rect);

std::optional<Point> next_point_in_circle(std::optional<Point> &point, Circle const& circle);

void mark_connected_pixels_as_visited(Point const& point, Circle const& circle,
                                      std::optional<std::vector<Point>> &visited_points);

pixel_class* get_pixel(Point const& p);

void discover_bounds(Point const& point, Rect& discovered);

bool is_button_color(pixel_class const& px);

Button assess_button(Rect const& bounds);

int count_button_holes_within(Circle const& circle);

bool do_any_match(std::vector<Point> const& points,
                  bool (*predicate_fn)(pixel_class const& p));

bool is_not_button_color(pixel_class const& px);

void draw_points(std::vector<Point> const& points, Color const& color);

#endif //ALGORITHMS_H
