#ifndef BUTTON_H
#define BUTTON_H

#include "rect.h"

struct Button {
    Rect bounds;
    bool is_broken{};
};

#endif //BUTTON_H
