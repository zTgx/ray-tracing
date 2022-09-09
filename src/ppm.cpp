#include <fstream>
#include "vec3.h"

void DrawPPM()
{
    int nx = 200;
    int ny = 100;

    std::ofstream ppm;
    ppm.open ("ppm.ppm");

    ppm << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j=ny-1;j>=0;j--) 
    {
        for(int i=0;i<nx;i++)
        {
            vec3 color = vec3(i * 1.0 / nx * 1.0, j * 1.0 / ny * 1.0, 0.2);

            int ir = static_cast<int>(255.99 * color[0]);
            int ig = static_cast<int>(255.99 * color[1]);
            int ib = static_cast<int>(255.99 * color[2]);

            ppm << ir << " " << ig << " " << ib << "\n";
        }
    }
}