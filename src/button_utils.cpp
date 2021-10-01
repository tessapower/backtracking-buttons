#include "pixel_class.h"
#include "button_utils.h"
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
};

// Iterates over image to find and color buttons
void process_image() {
    std::optional<Coord> coord;
    while ((coord = next_coord(*coord)) != std::nullopt) {
        pixel_class *p = get_pixel(*coord);

        if (is_button_color(*p) && !p->getexclude()) {
            fill_button(*coord);
        }

        p->setexclude(true);
    }

    // check if broken
    // draw red/green box
}

// returns if the pixel is the color of a button
bool is_button_color(pixel_class const& p) {
    return (p.getR() > 128);
}

// Fills the pixels of a button with a different color
void fill_button(Coord coord) {
    auto *p = get_pixel(coord);

    // basecase
    if ((p == nullptr) || p->getexclude() || !is_button_color(*p)) {
        return;
    }

    // do the thing
    p->setexclude(true);
    p->loaddata(255, 0, 0);

    // recurse
    for (auto& c : coord.neighbors()) {
        fill_button(c);
    }
}

pixel_class* get_pixel(Coord const& c) {
    return &picture[c.y][c.x];
}
