#include <iostream>
#include <fstream>

#include "../include/button_utils.h"
#include "../include/Pixel.h"

void load_buttons(std::string const& input_filename) {
    std::fstream input_file;

    input_file.open(input_filename.c_str(), std::fstream::in);

    if (!input_file.is_open()) {
        throw std::runtime_error("Unable to read from " + input_filename);
    }

    std::string line;
    // Skip over the line containing "P3", the "magic" PPM identifier
    // which indicates this is an RGB color image in ASCII
    getline(input_file, line);
    // Skip over the line containing the filename
    getline(input_file, line);

    input_file >> screen_x >> screen_y;  // size of image
    input_file >> max_colours;           // max number colors

    for (int y = 0; y < screen_y; y++) {
        for (int x = 0; x < screen_x; x++) {
            int R, G, B;
            input_file >> R >> G >> B;
            picture[x][y].set_rgb_values(R, G, B);
            picture[x][y].set_seen(false);
        }
    }

    input_file.close();
}

//void load_buttons() {
//    // load the picture from Buttons.ppm
//    int x, y, R, G, B;
//    std::fstream infile;
//    std::string infilename, line;
//    infilename = "Buttons.ppm";
//    infile.open(infilename.c_str(), std::fstream::in);
//    if (infile.is_open() == false) {
//        std::cout << "ERROR: not able to open " << infilename << std::endl;
//        exit(2);
//    }
//    getline(infile, line);  // this line is "P3"
//    getline(infile, line);  // this line is "# filename"
//    infile >> screen_x >> screen_y;  // this line is the size
//    infile >> max_colours;  // this line is 256
//    for (y = 0; y < screen_y; y++) {
//        for (x = 0; x < screen_x; x++) {
//            infile >> R >> G >> B;
//            picture[x][y].set_rgb_values(R, G, B);
//            picture[x][y].set_seen(false);
//        }
//    }
//    infile.close();
//}

void process_buttons() {
    // find button
    for (int y = 0; y < screen_y; y++) {
        for (int x = 0; x < screen_x; x++) {
            (is_button(picture[y][x]))
                ? picture[y][x].set_rgb_values(98, 167, 135)
                : picture[y][x].set_rgb_values(0, 0, 0);
        }
    }

    // check if broken
    // draw red/green box

    /*   D
     * B A C
     *   E
     *          [y-1, x]
     * [y, x-1] [y,   x]  [y, x+1]
     *          [y+1, x]
     *
     * Find pixel A at location (x, y) and look for all connected pixels by:
    Find pixel B at location (x – 1, y) and look for all connected pixels;
    Find pixel C at location (x + 1, y) and look for all connected pixels;
    Find pixel D at location (x, y – 1) and look for all connected pixels;
    Find pixel E at location (x, y + 1) and look for all connected pixels;

    This is a recursive algorithm – find the pixels connected to A by finding the pixels connected to B, etc.
    While this may not look like the famous “caves” program, it is essentially the same situation. And we
    have the same problem. We could develop an infinite loop where pixel A checks pixel B which checks
    pixel A which checks pixel B, etc. And we solve the problem in the same way, i.e. we put a boolean into
    each pixel and as soon as we have checked a pixel we exclude it from the search. Do not check that pixel
    again.

     */
}

bool is_button(Pixel const& p) {
    return p.red() > 128;
}

void output_result(std::string const& output_filename) {
    std::fstream output_file;
    output_file.open(output_filename.c_str(), std::fstream::out);

    if (!output_file.is_open()) {
        throw std::runtime_error("Unable to write to " + output_filename);
    }

    // .ppm file formatting
    output_file << "P3" << std::endl;
    output_file << "# " << output_filename << std::endl;

    output_file << screen_x << " " << screen_y << std::endl;
    output_file << max_colours << std::endl;

    // pixel rgb values

    for (int y = 0; y < screen_y; ++y) {
        for (int x = 0; x < screen_x; ++x) {
            Pixel p = picture[x][y];
            output_file << p;
        }
        output_file << std::endl;
    }

    output_file.close();
    std::cout << "Funush!" << std::endl;
}
