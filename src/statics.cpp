#include "statics.h"

int screenx, screeny, maxcolours;   // you must use these
img::pixel_class picture[600][600]; // you must use this
const geom::Rect image_rect{0, screenx - 1, 0, screeny - 1};
