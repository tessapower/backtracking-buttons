#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

#include "../include/button_utils.h"

void loadButtons();

#define INPUT_FILE "../tests/Buttons.ppm"
#define OUTPUT_FILE "../tests/Buttons_processed.ppm"

int main() {
    try {
        load_buttons(INPUT_FILE);
//        load_buttons();

        process_buttons();
        output_result(OUTPUT_FILE);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
