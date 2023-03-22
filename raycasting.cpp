#include "colour.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

float hit_sphere(const point3& center, float radius, const ray& r) {
    point3 oc = r.origin() - center;
    float a = r.direction().len_sq();
    float half_b = dot(oc, r.direction());
    float c = oc.len_sq() - radius*radius;
    float discriminant = half_b*half_b - a*c;
    if (discriminant < 0) {
        return -1.0f;
    }
    return (-half_b - sqrt(discriminant)) / a;
}

colour ray_colour(const ray& r) {
    float t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0f) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5f * colour(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

int main() {
    
    // Image properties
    const float aspect_ratio = 16.0 / 9.0;
    const int img_w = 1920;
    const int img_h = static_cast<int>(img_w / aspect_ratio);

    // Camera properties
    float viewport_h = 2.0;
    float viewport_w = aspect_ratio * viewport_h;
    float focal_len = 1.0;

    point3 origin(0, 0, 0);             // Camera location
    vec3 horizontal(viewport_w, 0, 0);
    vec3 vertical(0, viewport_h, 0);
    point3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_len);

    // Rendering

    FILE* ppm;
    char write_file[] = "ballNormals.ppm";
    ppm = fopen(write_file, "w");
    fprintf(ppm, "P3\n%d %d\n255\n", img_w, img_h);
    
    float u, v;
    for (int i = img_h - 1; i >= 0; i--) {
        cout << "\rScanlines remaining: " << i << " " << flush;
        for (int j = 0; j < img_w; j++) {
            u = float(j) / (img_w - 1);
            v = float(i) / (img_h - 1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            colour pixel = ray_colour(r);
            write_colour(ppm, pixel);
        }
    }

    fclose(ppm);

}