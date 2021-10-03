#include <cmath>

#include "button.h"
#include "algorithms.h"
#include "circle.h"
#include "color.h"
#include "coord.h"
#include "pixel_class.h"
#include "statics.h"

// TODO: Document works for any size button
// TODO: Document C++ standard
// TODO: Document Styleguide

// Setting this to true will visually color all test points in the output image.
// This is useful to visualise the process of checking for a broken buttons.
#define DEBUG_VISUALIZATIONS true

std::optional<Coord> next_coord(Coord current) {
    // TODO: comment this function
    std::optional<Coord> next = current;
    if (current.x < screenx - 1) {
        next->x += 1;
    } else {
        next->x = 0;
        next->y += 1;
    }

    return (next->y >= screeny) ? std::nullopt : next;
}

// Iterates over image to find and color buttons
void process_image() {
    // TODO: comment this function
    std::vector<Bounds> button_bounds = discover_button_bounds();
    std::vector<Button> buttons = assess_buttons(button_bounds);

    for (auto const& b : assessed_buttons) {

        if (b.pass) {
            draw_points(b.bounds.points_on_bounds(), kColorGreen);
        } else {
            draw_points(b.bounds.points_on_bounds(), kColorRed);
        }

    }
}

// TODO: comment this function
std::vector<Bounds> discover_button_bounds() {
    std::optional<Coord> coord;
    std::vector<Bounds> buttons = {};
    while ((coord = next_coord(*coord)) != std::nullopt) {
        auto *p = get_pixel(*coord);

        if (is_button_color(*p) && !p->getexclude()) {
            Bounds button_bounds(coord->x, coord->x, coord->y, coord->y);
            discover_bounds(*coord, button);
            buttons.push_back(button);
        }

        #if DEBUG_VISUALIZATIONS
            if (!is_button_color(*p)) {
                p->loaddata(0, 0, 0);
            }
        #endif

        p->setexclude(true);
    }

    return buttons;
}

std::vector<Button> assess_buttons(std::vector<Bounds> const& bounds) {
    // TODO: comment this function
    std::vector<Button> assessed_buttons;

    for (auto const& b : bounds) {
        // inner circle
        int radius = static_cast<int>((std::max(b.width(), b.height())/2.0)*0.93);
        const Circle inner{b.center(), radius};
        std::vector<Coord> inner_test_points = inner.points_on_circumference();
        bool pass = true;
        for (auto& point : inner_test_points) {
            auto *p = get_pixel(point);
            if (p != nullptr) {
                if (!is_button_color(*p)) {
                    pass = false;
                    break;
                }
            }
        }

        // outer circle
        radius = static_cast<int>((std::max(b.width(), b.height())/2.0)*1.2);
        const Circle outer{b.center(), radius};
        std::vector<Coord> outer_test_points = outer.points_on_circumference();
        for (auto& point : outer_test_points) {
            auto *p = get_pixel(point);
            if (p != nullptr) {
                if (is_button_color(*p)) {
                    pass = false;
                    break;
                }
            }
        }

        // check for 4 discrete islands

        assessed_buttons.emplace_back(Button{b, pass});
    }


    return assessed_buttons;
}

// returns if the pixel is the color of a button
bool is_button_color(pixel_class const& p) {
    return p.getR() > 128;
}

bool is_not_button_color(pixel_class const& p) {
    return !is_button_color(p);
}

// find the boundary of a discovered button by finding all connected pixels
void discover_bounds(Coord const& coord, Bounds& discovered) {
    // TODO: tidy function comments
    // base case
    auto p = get_pixel(coord);
    if ((p == nullptr) || p->getexclude() || !is_button_color(*p)) {
        return;
    }

    // do the thing
    p->setexclude(true);
//    p->loaddata(0, 255, 0);
    discovered.expand_to_include(coord);

    // recurse
    for (auto& c : coord.neighbors()) {
        discover_bounds(c, discovered);
    }
}

pixel_class* get_pixel(Coord const& c) {
    // TODO: add function comments
    return (c.x >= 0 && c.x < screenx && c.y >= 0 && c.y < screeny)
        ? &picture[c.y][c.x]
        : nullptr;
}

void draw_points(std::vector<Coord> const& coords, Color const& color) {
    // TODO: add function comments
    for (auto& c : coords) {
        auto p = get_pixel(c);
        if (p != nullptr) {
            p->loaddata(color.R, color.G, color.B);
        }
    }
}
