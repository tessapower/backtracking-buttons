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
#define DEBUG_VISUALIZATIONS false

void process_image() {
    for (auto const& bounds : discover_all_button_bounds()) {
        bool is_broken = false;

        // Draw two concentric circles and require that the pixellated edge of the
        // button image falls between them.
        const int radius = static_cast<int>(std::max(bounds.width(), bounds.height()) / 2.0);
        const int inner_radius = static_cast<int>(radius * 0.9);
        const int outer_radius = static_cast<int>(radius * 1.2);

        const Circle inner{bounds.center(), inner_radius};
        const Circle outer{bounds.center(), outer_radius};

        // TODO: replace with unary predicate
        is_broken |= do_any_match(inner.points_on_circumference(), &is_not_button_color);
        is_broken |= do_any_match(outer.points_on_circumference(), &is_button_color);
        is_broken |= num_enclosed_button_holes(inner.bounding_box()) != kNumRequiredButtonHoles;

#if DEBUG_VISUALIZATIONS
        draw_points(inner.points_on_circumference(), Color::LightBlue());
        draw_points(outer.points_on_circumference(), Color::LightBlue());
#endif

        Color status_color = is_broken ? Color::Red() : Color::Green();
        draw_points(bounds.points_on_perimeter(), status_color);
    }
}

int num_enclosed_button_holes(Rect const& bounds) {
    int num_btn_holes = 0;

    // Iterate over the pixels within the bounding box of the button and flip
    // their exclude  status. Then the pixels are in a "clean" slate.
    //
    for (auto const& point : bounds) {
        get_pixel(point)->setexclude(false);
    }

    for (auto const& point : bounds) {
        auto px = get_pixel(point);
        if (!px) {
            continue;
        }

        const bool did_discover_new_empty_area = is_not_button_color(*px) && !px->getexclude();
        if (did_discover_new_empty_area) {
            std::optional<std::vector<Point>> visited = std::nullopt;

#if DEBUG_VISUALIZATIONS
            visited = std::vector<Point>{};
#endif

            // If the connected pixels touch the bounds, then the empty area
            // discovered isn't a fully enclosed button hole
            //
            bool does_touch_bounds = discover_extent_of_connected_points(
                    point, bounds, visited);

            if (!does_touch_bounds) {
                num_btn_holes += 1;
#if DEBUG_VISUALIZATIONS
                draw_points(*visited, Color::LightBlue());
#endif
            }
        }

        px->setexclude(true);
    }

    return num_btn_holes;
}

// The visited parameter is optional; if you provide it, it will be filled with
// all points discovered while searching for the extent of connected points.
bool discover_extent_of_connected_points(Point const& point, Rect const& bounds,
                                         std::optional<std::vector<Point>> &visited) {
    auto px = get_pixel(point);
    if (px->getexclude() || is_button_color(*px)) {
        return false;
    }

    // Tracking visited points is optional so points are only appended to the
    // vector if a vector is provided.
    if (visited) {
        visited->emplace_back(point);
    }
    px->setexclude(true);

    bool does_touch_bounds = bounds.is_point_on_perimeter(point);
    for (auto const& p : point.neighbors()) {
        if (!bounds.contains_point(p)) {
            continue;
        }

        does_touch_bounds |= discover_extent_of_connected_points(p, bounds,visited);
    }

    return does_touch_bounds;
}

std::vector<Rect> discover_all_button_bounds() {
    std::vector<Rect> bounds_of_buttons;

    Rect image_rect = Rect{0, screenx, 0, screeny};
    for (auto const& point : image_rect) {
        auto px = get_pixel(point);
        if (!px) {
            continue;
        }

        const bool did_discover_new_button = is_button_color(*px) && !px->getexclude();
        if (did_discover_new_button) {
            // Initialize our bounds to a 0-by-0 box which discover_bounds expands
            Rect button_bounds(point.x, point.x, point.y, point.y);
            discover_bounds(point, button_bounds);
            bounds_of_buttons.emplace_back(button_bounds);
        }

        px->setexclude(true);
    }

    return bounds_of_buttons;
}

pixel_class* get_pixel(Point const& p) {
    return (p.x >= 0 && p.x < screenx && p.y >= 0 && p.y < screeny)
           ? &picture[p.y][p.x]
           : nullptr;
}

void discover_bounds(Point const& point, Rect& discovered) {
    auto px = get_pixel(point);
    if ((px == nullptr) || px->getexclude() || is_not_button_color(*px)) {
        return;
    }

    px->setexclude(true);
    discovered.expand_to_include(point);

    for (auto const& p : point.neighbors()) {
        discover_bounds(p, discovered);
    }
}

bool is_button_color(pixel_class const& px) {
    return px.getR() > 128;
}

bool is_not_button_color(pixel_class const& px) {
    return !is_button_color(px);
}

// FIXME: How do STL unary predicate functions/lambdas work?
bool do_any_match(std::vector<Point> const& points, bool (*predicate_fn)(pixel_class const& p)) {
    for (auto const& p : points) {
        auto px = get_pixel(p);
        if (px != nullptr) {
            if (predicate_fn(*px)) {
                return true;
            }
        }
    }

    return false;
}

void draw_points(std::vector<Point> const& points, Color const& color) {
    for (auto const& p : points) {
        auto px = get_pixel(p);
        if (px != nullptr) {
            px->loaddata(color.R, color.G, color.B);
        }
    }
}
