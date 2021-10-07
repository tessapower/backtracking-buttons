#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <functional>
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

using PointPredicate = std::function<bool(Point const&)>;
using MaybePointVector = std::reference_wrapper<std::vector<Point>>;

/**
 * Discovers the extent of points that are deemed connected to the given point.
 * @param[in] point The point to start discovering from.
 * @param[in, out] discovered_extent A Rect which will be grown to fit all the
 * connected points as they are discovered.
 * @param[in] pred_fn A predicate function which points must pass to be
 * considered part of the discovered extent.
 *  * @param[out] discovered_points An optional vector which, if provided, will be
 * filled with all discovered points.
 */
void discover_extent_of_connected_points(
        Point const& point,
        Rect &discovered_extent,
        PointPredicate const& pred_fn,
        OptionalPointVecRef discovered_points = std::nullopt);

int num_button_holes(Rect const& bounds);

bool is_part_of_button(Point const& point);

void draw_points(std::vector<Point> const& points, Color const& color);

pixel_class* get_pixel(Point const& p);

#endif //ALGORITHMS_H
