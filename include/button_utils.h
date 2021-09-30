#ifndef BUTTON_UTILS_H
#define BUTTON_UTILS_H

static int total, x_min, x_max, y_min, y_max;  // MUST be global if used
static int screen_x, screen_y, max_colours;    // you must use these

/**
 *
 * @param input_file
 */
void load_buttons(std::string const& input_file);

/**
 *
 * @param output_file
 */
void process_buttons(std::string const& output_file);

#endif //BUTTON_UTILS_H
