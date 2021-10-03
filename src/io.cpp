#include <fstream>
#include "io.h"
#include "statics.h"

// WARNING: This function cannot be altered and may exit the program!
void loadButtons() {
    // load the picture from Buttons.ppm
    int x, y, R, G, B;
    std::fstream infile;
    std::string infilename, line;
    // TODO: Update the filepath to original
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
}
