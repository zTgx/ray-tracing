#include <fstream>
#include "ray.h"

vec3 color(const ray& r)
{
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);

    vec3 a = vec3(1.0, 1.0, 1.0) * (1.0 - t);
    a += vec3(0.5, 0.7, 1.0) * t;

    return a;
}

void DrawPPM()
{
    int nx = 200;
    int ny = 100;

    std::ofstream ppm;
    ppm.open ("ppm.ppm");

    ppm << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizon(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for(int j=ny-1;j>=0;j--) 
    {
        for(int i=0;i<nx;i++)
        {
            float u = i * 1.0 / nx * 1.0;
            float v = j * 1.0 / ny * 1.0;

            ray r(origin, lower_left_corner + horizon * u + vertical * v);
            vec3 color = ::color(r);

            int ir = static_cast<int>(255.99 * color[0]);
            int ig = static_cast<int>(255.99 * color[1]);
            int ib = static_cast<int>(255.99 * color[2]);

            ppm << ir << " " << ig << " " << ib << "\n";
        }
    }
}