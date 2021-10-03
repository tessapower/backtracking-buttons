#include <cmath>

#include "button.h"
#include "algorithms.h"
#include "circle.h"
#include "color.h"
#include "pixel_class.h"
#include "point.h"
#include "statics.h"

// TODO: Document works for any size button
// TODO: Document C++ standard
// TODO: Document Styleguide

// Setting this to true will visually color all test points in the output image.
// This is useful to visualise the process of checking for a broken buttons.
#define DEBUG_VISUALIZATIONS true

// TODO: comment this function
void process_image() {
    const std::vector<Button> buttons = create_buttons(discover_all_button_bounds());

    for (auto const& button : buttons) {
        draw_points(button.bounds.points_on_perimeter(),
                    button.is_broken ? kColorRed : kColorGreen);
    }
}

// TODO: comment this function
std::vector<Button> create_buttons(std::vector<Rect> const& button_bounds) {
    std::vector<Button> buttons;

    buttons.reserve(button_bounds.size());
    for (auto& b : button_bounds) {
        buttons.emplace_back(assess_button(b));
    }

    return buttons;
}

// TODO: comment this function
Button assess_button(Rect const& bounds) {
    bool is_broken = false;

    const int radius = static_cast<int>(std::max(bounds.width(), bounds.height()) / 2.0);
    const int inner_radius = static_cast<int>(radius * 0.9);
    const int outer_radius = static_cast<int>(radius * 1.2);

    const Circle inner{bounds.center(), inner_radius};
    const Circle outer{bounds.center(), outer_radius};

    is_broken |= do_any_match(inner.points_on_circumference(), &is_not_button_color);
    is_broken |= do_any_match(outer.points_on_circumference(), &is_button_color);

    int num_btn_holes = 0;
    // check for 4 discrete islands

#if DEBUG_VISUALIZATIONS
    draw_points(inner.points_on_circumference(), kColorLightBlue);
    draw_points(outer.points_on_circumference(), kColorLightBlue);
#endif

    return Button{bounds, is_broken, num_btn_holes};
}

// TODO: comment this function
std::vector<Rect> discover_all_button_bounds() {
    std::vector<Rect> bounds_of_buttons;

    std::optional<Point> point;
    while ((point = next_point(*point))) {
        auto p = get_pixel(*point);

        const bool did_discover_new_button = is_button_color(*p) && !p->getexclude();
        if (did_discover_new_button) {
            // Initialize our bounds to a 0-by-0 box which discover_bounds expands
            Rect button_bounds(point->x, point->x, point->y, point->y);
            discover_bounds(*point, button_bounds);
            bounds_of_buttons.emplace_back(button_bounds);
        }

#if DEBUG_VISUALIZATIONS
        if (!is_button_color(*p)) {
            p->loaddata(kColorBlack.R, kColorBlack.G, kColorBlack.B);
        }
#endif

        p->setexclude(true);
    }

    return bounds_of_buttons;
}

// TODO: comment this function
std::optional<Point> next_point(Point current) {
    // TODO: comment this function
    std::optional<Point> next = current;
    if (current.x < screenx - 1) {
        next->x += 1;
    } else {
        next->x = 0;
        next->y += 1;
    }

    return (next->y >= screeny) ? std::nullopt : next;
}

// TODO: comment this function
pixel_class* get_pixel(Point const& p) {
    // TODO: add function comments
    return (p.x >= 0 && p.x < screenx && p.y >= 0 && p.y < screeny)
           ? &picture[p.y][p.x]
           : nullptr;
}

// TODO: comment this function
// find the boundary of a discovered button by finding all connected pixels
void discover_bounds(Point const& point, Rect& discovered) {
    // TODO: tidy function comments
    // base case
    auto px = get_pixel(point);
    if ((px == nullptr) || px->getexclude() || !is_button_color(*px)) {
        return;
    }

    // do the thing
    px->setexclude(true);
    discovered.expand_to_include(point);

    // recurse
    for (auto& p : point.neighbors()) {
        discover_bounds(p, discovered);
    }
}

// TODO: comment this function
// returns if the pixel is the color of a button
bool is_button_color(pixel_class const& px) {
    return px.getR() > 128;
}

// TODO: comment this function
bool do_any_match(std::vector<Point> const& points, bool (*predicate_fn)(pixel_class const& p)) {
    for (auto& point : points) {
        auto p = get_pixel(point);
        if (p != nullptr) {
            if (predicate_fn(*p)) {
                return true;
            }
        }
    }

    return false;
}

// TODO: comment this function
bool is_not_button_color(pixel_class const& px) {
    return !is_button_color(px);
}

// TODO: comment this function
void draw_points(std::vector<Point> const& points, Color const& color) {
    for (auto& p : points) {
        auto px = get_pixel(p);
        if (px != nullptr) {
            px->loaddata(color.R, color.G, color.B);
        }
    }
}
