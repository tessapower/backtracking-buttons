#ifndef IMG_H
#define IMG_H

#include "color.h"
#include "pixel_class.h"
#include "point.h"
#include <string>

namespace img {

void loadButtons();

void saveButtons(std::string const &output_filename);

bool is_part_of_button(geom::Point const &point);

void draw_point(geom::Point const &p, geom::Color const &color);

pixel_class *get_pixel(geom::Point const &p);

} // namespace img

#endif // IMG_H
