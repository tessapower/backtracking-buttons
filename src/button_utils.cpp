#include "../include/button_utils.h"

void load_buttons(std::string const& input_filename) {
    std::fstream input_file;

    input_file.open(input_filename.c_str(), fstream::in);

    if (!input_file.is_open()) {
        throw std::runtime_error("Unable to read from " + input_filename);
    }

    std::string line;
    // Skip over the line containing "P3", the "magic" PPM identifier
    // which indicates this is an RGB color image in ASCII
    getline(in_file, line);
    // Skip over the line containing the filename
    getline(in_file, line);

    in_file >> screen_x >> screen_y;  // size of image
    in_file >> max_colours;           // max number colors

    for (int y = 0; y < screen_y; y++) {
        for (int x = 0; x < screen_x; x++) {
            uint8_t R, G, B;
            in_file >> R >> G >> B;
            picture[x][y].set_rgb_value(R, G, B);
            picture[x][y].set_seen(false);
        }
    }

    in_file.close();
}

void process_buttons(std::string const& output_filename) {
    std::fstream output_file;
    output_file.open(output_filename.c_str(), std::fstream::out | std::fstream::app);

    if (!output_file.is_open()) {
        throw std::runtime_error("Unable to write to " + output_filename);
    }

    for (auto& p : picture) {
        out_file << p << std::endl;
    }

    out_file.close();
}
