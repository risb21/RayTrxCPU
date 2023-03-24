#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "consts.h"

struct hit_record;

class material {
public:
    virtual bool scatter(const ray& r, const hit_record& rec, colour& attenuation, ray& scattered) const = 0;
};

#endif