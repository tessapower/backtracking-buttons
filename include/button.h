#ifndef BUTTON_H
#define BUTTON_H

#include "rect.h"

struct Button {
    Rect bounds;
    bool is_broken{};
    int num_button_holes{0};
};

#endif //BUTTON_H
