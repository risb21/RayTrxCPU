#pragma once

#ifndef CONSTS_H
#define CONSTS_H

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.141592653589;

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}

/* Returns random float between  0 and 1, 0 inclusive */
inline float rand_float() {
    return rand() / (RAND_MAX + 1.0);
}

/* Returns random float between min and max, min inclusive */
inline float rand_float(float min, float max) {
    return min + (max - min) * rand_float();
}

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#include "ray.h"
#include "vec3.h"

#endif