#include "colour.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

colour ray_colour(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

int main() {
    
    // Image properties
    const float aspect_ratio = 16.0 / 9.0;
    const int imgW = 1920;
    const int imgH = static_cast<int>(imgW / aspect_ratio);

    // Camera properties
    float viewportH = 2.0;
    float viewportW = aspect_ratio * viewportH;
    float focalLen = 1.0;

    point3 origin(0, 0, 0);             // Camera location
    vec3 horizontal(viewportW, 0, 0);
    vec3 vertical(0, viewportH, 0);
    point3 lowerLeftCorner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focalLen);

    // Rendering

    FILE* ppm;
    char writefile[] = "Gradient.ppm";
    ppm = fopen(writefile, "w");
    fprintf(ppm, "P3\n%d %d\n255\n", imgW, imgH);
    
    float u, v;
    for (int i = imgH - 1; i >= 0; i--) {
        cout << "\rScanlines remaining: " << i << " " << flush;
        for (int j = 0; j < imgW; j++) {
            u = float(j) / (imgW - 1);
            v = float(i) / (imgH - 1);
            ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
            colour pixel = ray_colour(r);

            write_colour(ppm, pixel);
        }
    }

    fclose(ppm);

}