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

auto alg::process_scan(img::Scan const& scan) -> img::Scan {
  auto output_scan = scan;

  for (auto const& bounds : alg::discover_all_button_bounds(output_scan)) {
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
                             outer_circumference.end(), [&](auto pt) {
                               auto pixel = output_scan.get_pixel(pt);
                               return alg::is_part_of_button(pixel);
                             });

    is_broken |= std::any_of(inner_circumference.begin(),
                             inner_circumference.end(), [&](auto pt) {
                               auto pixel = output_scan.get_pixel(pt);
                               return !alg::is_part_of_button(pixel);
                             });

    is_broken |= alg::discover_num_button_holes(output_scan, inner.bounding_box()) !=
                 kNumRequiredButtonHoles;

#if DEBUG_VISUALIZATIONS
    for (auto const& point : outer_circumference) {
      img::draw_point(point, geom::Color::AzureBlue());
    }

    for (auto const& point : inner_circumference) {
      img::draw_point(point, geom::Color::AzureBlue());
    }
#endif

    geom::Color status_color =
        is_broken ? geom::Color::Red() : geom::Color::EmeraldGreen();
    for (auto const &point : bounds.perimeter()) {
      auto pixel = output_scan.get_pixel(point);
      pixel.change_color(status_color);
    }
  }

  return output_scan;
}

auto alg::discover_all_button_bounds(img::Scan& scan)
    -> std::vector<geom::Rect> {
  std::vector<geom::Rect> bounds_of_buttons;
  const geom::Rect scan_rect =
      geom::Rect{0, scan.screen_x() - 1, 0, scan.screen_y() - 1};

  for (auto const &point : scan_rect) {
    auto pixel = scan.get_pixel(point);

    const bool did_discover_new_button =
        is_part_of_button(pixel) && !pixel.visited();

    if (did_discover_new_button) {
      // Initialize our bounds to a 0-by-0 box which discover_bounds expands
      geom::Rect discovered_extent{point};
      alg::discover_extent_of_connected_points(
          scan, point, discovered_extent, [&](img::Pixel const& p) {
            return alg::is_part_of_button(p);
          });

      bounds_of_buttons.emplace_back(discovered_extent);
    }

    pixel.visited(true);
  }

  return bounds_of_buttons;
}

auto alg::is_part_of_button(img::Pixel const& pixel) noexcept -> bool {
  return pixel.red() > 128;
}

// The discovered_points parameter is optional; if provided, it will be filled
// with all points discovered while searching for the extent of connected points
auto alg::discover_extent_of_connected_points(
    img::Scan& scan, geom::Point const& point,
    geom::Rect& discovered_extent, PixelPredicate const& pred_fn,
    OptionalPointVecRef discovered_points) -> void {
  auto pixel = scan.get_pixel(point);
  if (pixel.visited() || !pred_fn(pixel)) {
    return;
  }

  // Tracking discovered points is optional so points are only appended to the
  // vector if a vector is provided
  if (discovered_points)
    discovered_points->get().emplace_back(point);

  pixel.visited(true);

  discovered_extent.expand_to_include(point);

  for (auto const& p : point.neighbors()) {
    discover_extent_of_connected_points(scan, p, discovered_extent, pred_fn,
                                        discovered_points);
  }
}

auto alg::discover_num_button_holes(img::Scan& scan, geom::Rect const& bounds)
    -> int {
  int num_btn_holes = 0;

  // Iterate over the pixels within the bounding box of the button and flip
  // their exclude status. Then the pixels are in a "clean" slate.
  for (auto const &point : bounds) {
    auto pixel = scan.get_pixel(point);
    pixel.visited(false);
  }

  for (auto const &point : bounds) {
    auto pixel = scan.get_pixel(point);

    const bool did_discover_new_empty_area =
        !alg::is_part_of_button(pixel) && !pixel.visited();

    if (did_discover_new_empty_area) {
#if DEBUG_VISUALIZATIONS
      std::vector<geom::Point> discovered_points{};
#endif
      geom::Rect discovered_extent = geom::Rect{point};

      discover_extent_of_connected_points(
          scan, point, discovered_extent,
          [&](img::Pixel const& p) {
            return !alg::is_part_of_button(p);
          }
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
        for (auto const& p : discovered_points) {
          img::draw_point(p, geom::Color::AzureBlue());
        }
#endif
      }
    }

    pixel.visited(true);
  }

  return num_btn_holes;
}
