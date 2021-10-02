#ifndef BUTTON_H
#define BUTTON_H

#include "bounds.h"

struct Button {
    Bounds bounds;
    bool pass{};
};

#endif //BUTTON_H
