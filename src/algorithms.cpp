#include "algorithms.h"
#include "circle.h"
#include "color.h"
#include "pixel_class.h"
#include "statics.h"

std::optional<Coord> next_coord(Coord current) {
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
    std::vector<Bounds> buttons = find_buttons();

    // check if buttons are broken

    for (auto const& b : buttons) {
        draw_bounding_box(b, kColorGreen);
    }
}

std::vector<Bounds> find_buttons() {
    std::optional<Coord> coord;
    std::vector<Bounds> buttons = {};
    while ((coord = next_coord(*coord)) != std::nullopt) {
        pixel_class *p = get_pixel(*coord);

        if (is_button_color(*p) && !p->getexclude()) {
            Bounds button(*coord);
            discover_bounds(*coord, button);
            buttons.push_back(button);
        }

        p->setexclude(true);
    }

    return buttons;
}

// returns if the pixel is the color of a button
bool is_button_color(pixel_class const& p) {
    return (p.getR() > 128);
}

// find the boundary of a discovered button by finding all connected pixels
void discover_bounds(Coord const& coord, Bounds& discovered) {
    // base case
    auto *p = get_pixel(coord);
    if ((p == nullptr) || p->getexclude() || !is_button_color(*p)) {
        return;
    }

    // do the thing
    p->setexclude(true);
    p->loaddata(0, 255, 0);
    discovered.expand_to_include(coord);

    // recurse
    for (auto& c : coord.neighbors()) {
        discover_bounds(c, discovered);
    }
}

pixel_class* get_pixel(Coord const& c) {
    return &picture[c.y][c.x];
}

void draw_points(std::vector<Coord> const& coords, Color const& color) {
    for (auto& c : coords) {
        get_pixel(c)->loaddata(color.R, color.G, color.B);
    }
}
