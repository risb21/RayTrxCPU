#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable {
public:
    point3 center;
    float radius;

    sphere() {}
    sphere(point3 cen, float r): center(cen), radius(r) {};

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    
    vec3 oc = r.origin() - center;          // Location of sphere origin
    float a = r.direction().len_sq();        
    float half_b = dot(oc, r.direction());  // Coeffs to find value of length of ray
    float c = oc.len_sq() - radius*radius;  // from camera till sphere intersection

    // Calculating discriminant
    float discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    float sqrtd = sqrt(discriminant);

    // Acceptable root according to constraints t_min and t_max
    float root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    rec.t = root;                               // Length of ray where sphere intersection happens
    rec.p = r.at(root);                         // Point of sphere intersection
    rec.normal = (rec.p - center) / radius;     // Normal at point p

    return true;
}   

#endif