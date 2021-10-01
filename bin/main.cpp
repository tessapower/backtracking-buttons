#include <cstdlib>
#include <fstream>
#include <iostream>

#include "../include/button_utils.h"
#include "../include/statics.h"

#define OUTPUT_FILE "../tests/Buttons_processed.ppm"

void loadButtons();

int main() {
    loadButtons();
    process_image();
    output_result(OUTPUT_FILE);

    return EXIT_SUCCESS;
}

// WARNING: This function cannot be altered and may exit the program!
void loadButtons() {
    // load the picture from Buttons.ppm
    int x, y, R, G, B;
    std::fstream infile;
    std::string infilename, line;
    infilename = "../tests/Buttons.ppm";
    infile.open(infilename.c_str(), std::fstream::in);
    if (infile.is_open() == false) {
        std::cout << "ERROR: not able to open " << infilename << std::endl;
        std::exit(2);
    }
    std::getline(infile, line);  // this line is "P3"
    std::getline(infile, line);  // this line is "# filename"
    infile >> screenx >> screeny;  // this line is the size
    infile >> maxcolours;  // this line is 256
    for (y = 0; y < screeny; y++) {
        for (x = 0; x < screenx; x++) {
            infile >> R >> G >> B;
            picture[y][x].loaddata(R, G, B);
            picture[y][x].setexclude(false);
        }
    }
    infile.close();
}
