#include <cstdlib>

#include "button_utils.h"
#include "file_io.h"

#define OUTPUT_FILE "../tests/Buttons_processed.ppm"

int main() {
    loadButtons();
    process_image();
    output_result(OUTPUT_FILE);

    return EXIT_SUCCESS;
}
