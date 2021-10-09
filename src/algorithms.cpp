#include <algorithm>
#include <cmath>

#include "algorithms.h"
#include "circle.h"
#include "color.h"
#include "pixel_class.h"
#include "point.h"
#include "statics.h"

constexpr int kNumRequiredButtonHoles = 4;

// TODO: Document works for any size button
// TODO: Document C++ standard
// TODO: Document Styleguide

// Setting this to true will visually color all test points in the output image.
// This is useful to visualise the process of checking for broken buttons.
#define DEBUG_VISUALIZATIONS true

void process_image() {
    for (auto const& bounds : discover_all_button_bounds()) {
        bool is_broken = false;

        // Draw two concentric circles and require that the pixelated edge of the
        // button image falls between them.
        const int radius = static_cast<int>(std::max(bounds.width(), bounds.height()) / 2.0);

        const Circle outer{bounds.center(), static_cast<int>(radius * 1.2)};
        const Circle inner{bounds.center(), static_cast<int>(radius * 0.9)};

        auto outer_circumference = outer.circumference();
        auto inner_circumference = inner.circumference();

        is_broken |= std::any_of(
                outer_circumference.begin(),
                outer_circumference.end(),
                is_part_of_button);

        is_broken |= std::any_of(
                inner_circumference.begin(),
                inner_circumference.end(),
                [](auto p) { return !is_part_of_button(p); });

        is_broken |= num_button_holes(inner.bounding_box()) != kNumRequiredButtonHoles;

#if DEBUG_VISUALIZATIONS
        for (auto const& point : outer_circumference) {
            draw_point(point, Color::AzureBlue());
        }
        for (auto const& point : inner_circumference) {
            draw_point(point, Color::AzureBlue());
        }
#endif

        Color status_color = is_broken ? Color::Red() : Color::EmeraldGreen();
        for (auto const& point : bounds.perimeter()) {
            draw_point(point, status_color);
        }
    }
}

std::vector<Rect> discover_all_button_bounds() {
    std::vector<Rect> bounds_of_buttons;

    for (auto const& point : image_rect) {
        auto px = get_pixel(point);
        if (!px) {
            continue;
        }

        const bool did_discover_new_button = is_part_of_button(point) && !px->getexclude();
        if (did_discover_new_button) {
            // Initialize our bounds to a 0-by-0 box which discover_bounds expands
            Rect discovered_extent(point);
            discover_extent_of_connected_points(
                    point,
                    discovered_extent,
                    [](Point const& point){ return is_part_of_button(point);});

            bounds_of_buttons.emplace_back(discovered_extent);
        }

        px->setexclude(true);
    }

    return bounds_of_buttons;
}

// The discovered_points parameter is optional; if provided, it will be filled
// with all points discovered while searching for the extent of connected points
void discover_extent_of_connected_points(Point const& point,
                                         Rect &discovered_extent,
                                         PointPredicate const& pred_fn,
                                         OptionalPointVecRef discovered_points) {
    auto px = get_pixel(point);
    if (!px || px->getexclude() || !pred_fn(point)) {
        return;
    }

    // Tracking discovered points is optional so points are only appended to the
    // vector if a vector is provided
    if (discovered_points) {
        discovered_points->get().emplace_back(point);
    }

    px->setexclude(true);
    discovered_extent.expand_to_include(point);

    for (auto const& p : point.neighbors()) {
        discover_extent_of_connected_points(
                p,discovered_extent, pred_fn, discovered_points);
    }
}

int num_button_holes(Rect const& bounds) {
    int num_btn_holes = 0;

    // Iterate over the pixels within the bounding box of the button and flip
    // their exclude status. Then the pixels are in a "clean" slate.
    //
    for (auto const& point : bounds) {
        get_pixel(point)->setexclude(false);
    }

    for (auto const& point : bounds) {
        auto px = get_pixel(point);
        if (!px) {
            continue;
        }

        const bool did_discover_new_empty_area = !is_part_of_button(point) && !px->getexclude();
        if (did_discover_new_empty_area) {
            std::vector<Point> discovered_points{};
            Rect discovered_extent = Rect{point};

            discover_extent_of_connected_points(
                    point,
                    discovered_extent,
                    [](Point const& p) {return !is_part_of_button(p);},
                    discovered_points);

            // If the connected pixels touch the bounds, then the empty area
            // discovered isn't a fully enclosed button hole
            if (discovered_extent.is_proper_subset_of(bounds)) {
                num_btn_holes += 1;
#if DEBUG_VISUALIZATIONS
                for (auto const& p : discovered_points) {
                    draw_point(p, Color::AzureBlue());
                }
#endif
            }
        }

        px->setexclude(true);
    }

    return num_btn_holes;
}

bool is_part_of_button(Point const& point) {
    auto px = get_pixel(point);
    if (px != nullptr) {
        return px->getR() > 128;
    }

    return false;
}

inline void draw_point(Point const& p, Color const& color) {
    auto px = get_pixel(p);
    if (px != nullptr) {
        px->loaddata(color.R, color.G, color.B);
    }
}

pixel_class* get_pixel(Point const& p) {
    return (p.x >= 0 && p.x < screenx && p.y >= 0 && p.y < screeny)
           ? &picture[p.y][p.x]
           : nullptr;
}
