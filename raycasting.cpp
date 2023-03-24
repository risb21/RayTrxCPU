#include "headers/consts.h"

#include "headers/colour.h"
#include "headers/hittable_list.h"
#include "headers/sphere.h"
#include "headers/camera.h"
#include "headers/material.h"

#include <iostream>

colour ray_colour(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if (depth <= 0) {
        return colour(0, 0, 0);
    }

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        colour attenuation;
        if (rec.mat_ptr -> scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_colour(scattered, world, depth-1);
        }
        return colour(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

int main() {
    
    // Image properties
    const float aspect_ratio = 16.0 / 9.0;
    const int img_w = 1920;
    const int img_h = static_cast<int>(img_w / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 20;
    
    // World definition
    hittable_list world;

    shared_ptr<lambertian> material_ground = make_shared<lambertian>(colour(0.8, 0.8, 0.0));
    shared_ptr<lambertian> material_center = make_shared<lambertian>(colour(0.7, 0.3, 0.3));
    shared_ptr<metal> material_left = make_shared<metal>(colour(0.8, 0.8, 0.8));
    shared_ptr<metal> material_right = make_shared<metal>(colour(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, material_ground));
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1, 0, -1.2), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1, 0, -1.2), 0.5, material_right));
    
    // Camera properties
    camera cam;

    // Rendering

    FILE* ppm;
    char write_file[] = "3Material.ppm";
    ppm = fopen(write_file, "w");
    fprintf(ppm, "P3\n%d %d\n255\n", img_w, img_h);
    
    float u, v;
    ray r;
    for (int i = img_h - 1; i >= 0; i--) {
        cout << "\rScanlines remaining: " << i << " " << flush;
        for (int j = 0; j < img_w; j++) {
            colour pixel(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                u = float(j + rand_float()) / (img_w - 1);
                v = float(i + rand_float()) / (img_h - 1);
                r = cam.get_ray(u, v);
                pixel += ray_colour(r, world, max_depth);
            }
            write_colour(ppm, pixel, samples_per_pixel);
        }
    }

    fclose(ppm);

}