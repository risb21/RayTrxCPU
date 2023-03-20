#pragma once

#include <iostream>
#include <cmath>

using namespace std;

class vec3 {
public:
    float v[3];

    vec3(float x = 0, float y = 0, float z = 0) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }

    float x() { return v[0]; }
    float y() { return v[1]; }
    float z() { return v[2]; }

    vec3 operator-() const { vec3(-v[0], -v[1], v[2]); }
    float operator[](int i) const { return v[i]; }
    float& operator[](int i) { return v[i]; }

    vec3& operator+=(const vec3 &a) {
        v[0] += a.v[0];
        v[1] += a.v[1];
        v[2] += a.v[2];
        return *this;
    }

    vec3& operator*=(const float t) {
        v[0] *= t;
        v[1] *= t;
        v[2] *= t;
        return *this;
    }

    vec3& operator/=(const float t) { return *this *= 1/t; }

    float len_sq() const { return v[0]*v[0] + v[1]*v[1]+ v[2]*v[2]; }
    float len() const { return sqrt(len_sq()); }


};

using point3 = vec3;
using colour = vec3;