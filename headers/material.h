#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "consts.h"
#include "hittable.h"

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const = 0;
};

class lambertian: public material {
public:
    colour albedo;

    lambertian(const colour& a) : albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const override {
        vec3 scatter_dir = rec.normal + random_unit_vector();
        
        // If scatter direction is close to a zero len vector
        if (scatter_dir.near_zero()) {
            scatter_dir = rec.normal;
        }
        
        scattered = ray(rec.p, scatter_dir);
        attenuation = albedo;
        return true;
    }
};

class metal: public material {
public:
    colour albedo;

    metal(const colour& a) : albedo(a) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, colour& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};

#endif