#ifndef BUTTON_UTILS_H
#define BUTTON_UTILS_H

#include <optional>
#include <string>

#include "Coord.h"
#include "pixel_class.h"

void process_image();

bool is_button_color(pixel_class const& p);

void fill_button(Coord coord);

pixel_class* get_pixel(Coord const& c);

void output_result(std::string const& output_filename);

#endif //BUTTON_UTILS_H
