#ifndef BUTTON_UTILS_H
#define BUTTON_UTILS_H

#include <string>
#include <Pixel.h>

static int total, x_min, x_max, y_min, y_max;  // MUST be global if used
static int screen_x, screen_y, max_colours;    // you must use these
static Pixel picture[600][600];

/**
 * Loads an image of black and white buttons from a .ppm file.
 * @param input_file The file to read in the image from
 */
void load_buttons(std::string const& input_file);
//void load_buttons();

void process_buttons();

bool is_button(Pixel const& p);

/**
 *
 * @param picture
 * @param output_filename
 */
void output_result(std::string const& output_filename);

#endif //BUTTON_UTILS_H
