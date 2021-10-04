#include <cmath>

#include "button.h"
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

// TODO: comment this function
void process_image() {
    const std::vector<Button> buttons = create_buttons(discover_all_button_bounds());

    for (auto const& button : buttons) {
        draw_points(button.bounds.points_on_perimeter(),
                    button.is_broken ? Color::Red() : Color::Green());
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
// TODO: probably move this whole thing into create_buttons?
Button assess_button(Rect const& bounds) {
    bool is_broken = false;

    const int radius = static_cast<int>(std::max(bounds.width(), bounds.height()) / 2.0);
    const int inner_radius = static_cast<int>(radius * 0.9);
    const int outer_radius = static_cast<int>(radius * 1.2);

    const Circle inner{bounds.center(), inner_radius};
    const Circle outer{bounds.center(), outer_radius};

    is_broken |= do_any_match(inner.points_on_circumference(), &is_not_button_color);
    is_broken |= do_any_match(outer.points_on_circumference(), &is_button_color);
    is_broken |= count_button_holes(bounds) != kNumRequiredButtonHoles;

#if DEBUG_VISUALIZATIONS
    draw_points(inner.points_on_circumference(), Color::LightBlue());
    draw_points(outer.points_on_circumference(), Color::LightBlue());
#endif

    return Button{bounds, is_broken};
}

int count_button_holes(Rect const& button_bounds) {
    int num_btn_holes = 0;

    // Iterate over the pixels within the buttons_bounds and flip their exclude
    // status. This is so we can iterate over the bounding box with a "clean slate".
    //
    // TODO: for next_point_in_circle -> setexclude(false)
    //  Decide whether standard next_point_in_rect/circle behaviour is inclusive
    //  or exclusive of boundaries. If different scenarios are necessary, set a flag.
    //  maybe Rect.expand_by(npx, npx) ?
    for (int y = button_bounds.min_y; y <= button_bounds.max_y; y++) {
        for (int x = button_bounds.min_x; x <= button_bounds.max_x; x++) {
            get_pixel(Point{x, y})->setexclude(false);
        }
    }

    // TODO: change this so we accept a std::optional and we know when we've
    //  dealing with the first point if == std::nullopt
    std::optional<Point> point = Point{button_bounds.min_x, button_bounds.min_y};

    // TODO: Iterate over circle
    while ((point = next_point_in_rect(*point, button_bounds))) {
        auto px = get_pixel(*point);

        const bool did_discover_new_empty_area = is_not_button_color(*px) && !px->getexclude();
        if (did_discover_new_empty_area) {
            std::optional<std::vector<Point>> visited_points = std::nullopt;
            // TODO: mark_connected_points_as_visited(std::optional<std::vector<Point>> &visited_points);
#if DEBUG_VISUALIZATIONS
            visited_points = std::vector<Point>{};
#endif
            if (!is_touching_bounding_box(*point, button_bounds, visited_points)) {
                num_btn_holes += 1;
#if DEBUG_VISUALIZATIONS
                draw_points(*visited_points, Color::LightBlue());
#endif
            }
        }

        px->setexclude(true);
    }

    return num_btn_holes;
}

// TODO: Document this too!
bool is_touching_bounding_box(Point const& point,
                              Rect const& button_bounds,
                              std::optional<std::vector<Point>> &visited_points) {
    auto pixel = get_pixel(point);
    if (pixel->getexclude() || is_button_color(*pixel)) {
        return false;
    }

    // Tracking visited points is optional so points are only appended to the
    // vector if a vector is provided.
    if (visited_points) {
        visited_points->emplace_back(point);
    }
    pixel->setexclude(true);

    bool is_point_touching = button_bounds.is_point_on_perimeter(point);
    for (auto& p : point.neighbors()) {
        if (!button_bounds.contains_point(p)) {
            continue;
        }
        is_point_touching |= is_touching_bounding_box(p, button_bounds, visited_points);
    }

    return is_point_touching;
}

// TODO: comment this function
std::vector<Rect> discover_all_button_bounds() {
    std::vector<Rect> bounds_of_buttons;

    Rect size_of_picture = Rect{0, screenx, 0, screeny};
    std::optional<Point> point;
    while ((point = next_point_in_rect(*point, size_of_picture))) {
        auto p = get_pixel(*point);

        const bool did_discover_new_button = is_button_color(*p) && !p->getexclude();
        if (did_discover_new_button) {
            // Initialize our bounds to a 0-by-0 box which discover_bounds expands
            Rect button_bounds(point->x, point->x, point->y, point->y);
            discover_bounds(*point, button_bounds);
            bounds_of_buttons.emplace_back(button_bounds);
        }

        p->setexclude(true);
    }

    return bounds_of_buttons;
}

// TODO: comment this function
std::optional<Point> next_point_in_rect(Point const& current, Rect const& rect) {
    std::optional<Point> next = current;
    if (current.x < rect.max_x - 1) {
        next->x += 1;
    } else {
        next->x = 0;
        next->y += 1;
    }

    return (next->y >= rect.max_y) ? std::nullopt : next;
}

// TODO: comment this function
pixel_class* get_pixel(Point const& p) {
    return (p.x >= 0 && p.x < screenx && p.y >= 0 && p.y < screeny)
           ? &picture[p.y][p.x]
           : nullptr;
}

// TODO: comment this function
// find the boundary of a discovered button by finding all connected pixels
void discover_bounds(Point const& point, Rect& discovered) {
    // base case
    auto px = get_pixel(point);
    if ((px == nullptr) || px->getexclude() || is_not_button_color(*px)) {
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
