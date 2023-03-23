#pragma once

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

// For instancing hittable object classes
using std::shared_ptr;
using std::make_shared;

class hittable_list: public hittable {

public:

    vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> object) { objects.push_back(object); } 

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

};

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_hit = t_max;

    for (const shared_ptr<hittable> object: objects) {
        if (object -> hit(r, t_min, closest_hit, temp_rec)) {
            hit_anything = true;
            closest_hit = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}


#endif