#include <cstdlib>

#include "algorithms.h"
#include "io.h"

#define OUTPUT_FILE "Buttons_processed.ppm"

int main() {
    loadButtons();
    process_image();
    output_result(OUTPUT_FILE);

    return EXIT_SUCCESS;
}
