#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include <geom/circle.h>
#include <geom/color.h>
#include <geom/point.h>
#include <geom/rect.h>
#include <img/pixel.h>
#include <img/scan.h>

using PixelPredicate = std::function<bool(img::Pixel const &)>;
using OptionalPointVecRef =
        std::optional<std::reference_wrapper<std::vector<geom::Point>>>;

namespace alg {
/**
 * The primary function which will discover all buttons,
 * categorize them as broken or not broken, and output a new
 * image. The image will contain the buttons with red boxes
 * to indicate broken buttons, or otherwise green for OK.
 *
 * Set DEBUG_VISUALIZATIONS to true to enable debug visualizations.
 */
    void process_image();

/**
 * Discovers all the bounding boxes for the buttons. It does not categorize
 * the buttons as broken or not broken.
 * @return A vector containing the bounds of all the buttons in the image.
 */
    std::vector<geom::Rect> discover_all_button_bounds();

auto is_part_of_button(img::Pixel const &pixel) noexcept -> bool;

/**
 * Discovers the extent of points that are deemed connected to the given point.
 * @param[in] point The point to start discovering from.
 * @param[in, out] discovered_extent A Rect which will be grown to fit all the
 * connected points as they are discovered.
 * @param[in] pred_fn A predicate function which points must pass to be
 * considered part of the discovered extent.
 * @param[out] discovered_points An optional vector which, if provided, will
 * be filled with all discovered points.
 */
auto discover_extent_of_connected_points(
    geom::Point const &point,
    geom::Rect &discovered_extent, PixelPredicate const &pred_fn,
    OptionalPointVecRef discovered_points = std::nullopt) -> void;

    int discover_num_button_holes(geom::Rect const &bounds);

} // namespace alg

#endif // ALGORITHMS_H