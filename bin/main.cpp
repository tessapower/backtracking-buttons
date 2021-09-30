#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

#include <pixel.h>
#include <button_utils.h>

void loadButtons();

#define INPUT_FILE "../tests/Buttons.ppm"
#define OUTPUT_FILE "../tests/Buttons_processed.ppm"

Pixel picture[600][600];

int main() {
    try {
        load_buttons(INPUT_FILE);
        process_buttons(OUTPUT_FILE);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
