#include <iostream>
#include <fstream>

int main()
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
            float r = i * 1.0 / nx * 1.0;
            float g = j * 1.0 / ny * 1.0;
            float b = 0.2;

            int ir = static_cast<int>(255.99 * r);
            int ig = static_cast<int>(255.99 * g);
            int ib = static_cast<int>(255.99 * b);

            ppm << ir << " " << ig << " " << ib << "\n";
        }
    }
}