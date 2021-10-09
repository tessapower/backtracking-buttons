#ifndef STATICS_H
#define STATICS_H

#include "pixel_class.h"
#include "rect.h"

extern int screenx, screeny, maxcolours;   // you must use these
extern img::pixel_class picture[600][600]; // you must use this
extern const geom::Rect image_rect;
constexpr int kNumRequiredButtonHoles = 4;

#endif // STATICS_H
