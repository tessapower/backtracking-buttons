#include <algorithm>

#include "algorithms.h"
#include <geom/circle.h>
#include <geom/color.h>
#include <geom/point.h>
#include <img/scan.h>

// Setting this to true will visually color all test points in the output image.
// This is useful to visualise the process of checking for broken buttons.
#define DEBUG_VISUALIZATIONS false

constexpr int kNumRequiredButtonHoles = 4;

void alg::process_image() {
    for (auto const &bounds : alg::discover_all_button_bounds()) {
        bool is_broken = false;

        // Draw two concentric circles and require that the pixelated edge of the
        // button image falls between them.
        const int radius =
                static_cast<int>(std::max(bounds.width(), bounds.height()) / 2.0);

        const geom::Circle outer{bounds.center(), static_cast<int>(radius * 1.2)};
        const geom::Circle inner{bounds.center(), static_cast<int>(radius * 0.9)};

        auto outer_circumference = outer.circumference();
        auto inner_circumference = inner.circumference();

        is_broken |= std::any_of(outer_circumference.begin(),
                                 outer_circumference.end(), img::is_part_of_button);

        is_broken |=
                std::any_of(inner_circumference.begin(), inner_circumference.end(),
                            [](auto p) { return !img::is_part_of_button(p); });

        is_broken |= alg::discover_num_button_holes(inner.bounding_box()) !=
                     kNumRequiredButtonHoles;

#if DEBUG_VISUALIZATIONS
    for (auto const &point : outer_circumference) {
      img::draw_point(point, geom::Color::AzureBlue());
    }

    for (auto const &point : inner_circumference) {
      img::draw_point(point, geom::Color::AzureBlue());
    }
#endif

    geom::Color status_color =
        is_broken ? geom::Color::Red() : geom::Color::EmeraldGreen();
    for (auto const &point : bounds.perimeter()) {
      img::draw_point(point, status_color);
    }
  }

std::vector<geom::Rect> alg::discover_all_button_bounds() {
    std::vector<geom::Rect> bounds_of_buttons;
    const geom::Rect image_rect = geom::Rect{0, screenx - 1, 0, screeny - 1};

    for (auto const &point : image_rect) {
        auto px = img::get_pixel(point);

        const bool did_discover_new_button =
                img::is_part_of_button(point) && !px->getexclude();

        if (did_discover_new_button) {
            // Initialize our bounds to a 0-by-0 box which discover_bounds expands
            geom::Rect discovered_extent{point};
            alg::discover_extent_of_connected_points(
                    point, discovered_extent, [](geom::Point const &point) {
                        return img::is_part_of_button(point);
                    });

            bounds_of_buttons.emplace_back(discovered_extent);
        }
    if (did_discover_new_button) {
      // Initialize our bounds to a 0-by-0 box which discover_bounds expands
      geom::Rect discovered_extent{point};
      alg::discover_extent_of_connected_points(
          point, discovered_extent, [&](img::Pixel const &px) {
            return alg::is_part_of_button(px);
          });

        px->setexclude(true);
    }

    return bounds_of_buttons;
}

auto alg::is_part_of_button(img::Pixel const &pixel) noexcept -> bool {
  return pixel.red() > 128;
}

// The discovered_points parameter is optional; if provided, it will be filled
// with all points discovered while searching for the extent of connected points
auto alg::discover_extent_of_connected_points(
    geom::Point const &point,
    geom::Rect &discovered_extent, PixelPredicate const &pred_fn,
    OptionalPointVecRef discovered_points) -> void {
  auto pixel = img::get_pixel(point);
  if (pixel.visited() || !pred_fn(pixel)) {
    return;
  }

  // Tracking discovered points is optional so points are only appended to the
  // vector if a vector is provided
  if (discovered_points)
    discovered_points->get().emplace_back(point);

  pixel.visited(true);

  discovered_extent.expand_to_include(point);

  for (auto const &p : point.neighbors()) {
    discover_extent_of_connected_points(p, discovered_extent, pred_fn,
                                        discovered_points);
  }
}

/**
 * Explores the area within the bounds (which is expected to be the bounds of a
 * button) to determine the number of button holes the button has.
 * @param bounds
 * @return The number of enclosed button holes the button has
 */
int alg::discover_num_button_holes(geom::Rect const &bounds) {
    int num_btn_holes = 0;

    // Iterate over the pixels within the bounding box of the button and flip
    // their exclude status. Then the pixels are in a "clean" slate.
    for (auto const &point : bounds) {
        img::get_pixel(point)->setexclude(false);
    }

    for (auto const &point : bounds) {
        auto px = img::get_pixel(point);
        if (!px) {
            continue;
        }

        const bool did_discover_new_empty_area =
                !img::is_part_of_button(point) && !px->getexclude();

        if (did_discover_new_empty_area) {
#if DEBUG_VISUALIZATIONS
      std::vector<geom::Point> discovered_points{};
#endif
      geom::Rect discovered_extent = geom::Rect{point};

            discover_extent_of_connected_points(
                    point, discovered_extent,
                    [](geom::Point const &p) { return !img::is_part_of_button(p); }
#if DEBUG_VISUALIZATIONS
          ,
          discovered_points
#endif
      );

      // If the connected pixels touch the bounds, then the empty area
      // discovered isn't a fully enclosed buttonhole. Conversely, if it
      // was then we have found a buttonhole.
      if (discovered_extent.is_fully_enclosed_by(bounds)) {
        num_btn_holes++;

#if DEBUG_VISUALIZATIONS
        for (auto const &p : discovered_points) {
          img::draw_point(p, geom::Color::AzureBlue());
        }
#endif
            }
        }

        px->setexclude(true);
    }

    return num_btn_holes;
}