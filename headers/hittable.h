#pragma once

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "consts.h"

class material;

struct hit_record {
    point3 p;
    vec3 normal;
    shared_ptr<material> mat_ptr;
    float t;
    bool front_face;

    /* Normal variable of hit_record is against incoming ray, i.e, it will always
       be in the opposite direction of the ray regardless of whether the ray is 
       intersecting from inside or outside the object */
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Is the ray hit outside the surface?
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif