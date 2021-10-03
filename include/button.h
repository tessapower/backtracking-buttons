#ifndef BUTTON_H
#define BUTTON_H

#include "bounds.h"

struct Button {
    Bounds bounds;
    bool is_broken{};
};

#endif //BUTTON_H
