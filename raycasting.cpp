#include "headers/consts.h"

#include "headers/colour.h"
#include "headers/hittable_list.h"
#include "headers/sphere.h"
#include "headers/camera.h"

#include <iostream>

colour ray_colour(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + colour(1, 1, 1));
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
    
    // World definition
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(1.2, 0, -1.5), 0.5));
    world.add(make_shared<sphere>(point3(-1.2, 0, -1.5), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    
    // Camera properties
    camera cam;
    float viewport_h = 2.0;
    float viewport_w = aspect_ratio * viewport_h;
    float focal_len = 1.0;

    point3 origin(0, 0, 0);             // Camera location
    vec3 horizontal(viewport_w, 0, 0);
    vec3 vertical(0, viewport_h, 0);
    point3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_len);

    // Rendering

    FILE* ppm;
    char write_file[] = "3ballsNormals.ppm";
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
                pixel += ray_colour(r, world);
            }
            write_colour(ppm, pixel, samples_per_pixel);
        }
    }

    fclose(ppm);

}