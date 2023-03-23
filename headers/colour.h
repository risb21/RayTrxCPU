#pragma once

#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include <cassert>

void write_colour(FILE* ppm, colour pixel) {
    fprintf(ppm, "%d %d %d\n",
            static_cast<int>(255.99 * pixel.x()),
            static_cast<int>(255.99 * pixel.y()),
            static_cast<int>(255.99 * pixel.z())
    );
}

#endif