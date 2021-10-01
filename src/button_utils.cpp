#include <iostream>
#include <fstream>

#include <pixel_class.h>
#include <button_utils.h>
#include <statics.h>

Coord next_coord(Coord current) {
    int x, y = current.y;
    if (current.x < screenx - 1) {
        x = current.x + 1;
    } else {
        x = 0;
        y = current.y + 1;
    }

    return Coord{x, y};
};

// Iterates over image to find and color buttons
void process_image() {
    Coord coord;
    pixel_class *p;

    while ((p = get_pixel(coord)) != nullptr) {
        if (is_button_color(*p) && !p->getexclude()) {
            fill_button(coord);
        }

        p->setexclude(true);

        coord = next_coord(coord);
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
    const bool is_within_x_bounds = (c.x < screenx) && (c.x >= 0);
    const bool is_within_y_bounds = (c.y < screeny) && (c.y >= 0);
    if (is_within_x_bounds && is_within_y_bounds) {
        return &picture[c.y][c.x];
    }

    return nullptr;
}

void output_result(std::string const& output_filename) {
   std::fstream output_file;
   std::cout << "Writing to " << output_filename << std::endl;
   output_file.open(output_filename.c_str(), std::fstream::out);
   if (!output_file.is_open()) {
       throw std::runtime_error("Unable to write to " + output_filename);
   }
   // Needed for .ppm file formatting
   output_file << "P3" << std::endl;
   output_file << "# " << output_filename << std::endl;
   output_file << screenx << " " << screeny << std::endl;
   output_file << maxcolours << std::endl;

   // pixel rgb values
   for (int y = 0; y < screeny; ++y) {
       for (int x = 0; x < screenx; ++x) {
           picture[y][x].datatofile(output_file);
       }
       output_file << std::endl;
   }
   output_file.close();
   std::cout << "Funush!" << std::endl;
}
