#pragma once

#include <iostream>
#include <fstream>
#include "vec3.h"

// http://users.csc.calpoly.edu/~akeen/courses/csc101/handouts/assignments/ppmformat.html#:~:text=The%20ppm%20P3%20format%20is,pixel%20in%20the%20next%20row).
// The header consists of :
// the characters P3, 
// the integer width of the image (in pixels), 
// the integer height of the image, 
// and the maximum value for a color component (we will use 255 for this value).
class PPM
{
    public:
        PPM() noexcept { ofs.open ("ppm.ppm"); }

    public:
        /** Header Format:
         * P3
         * width height
         * 255
         */
        void DrawHeader(const int width, const int height) { 
            ofs << "P3\n"; 
            ofs << width << " " << height << "\n"; 
            ofs << "255";
            ofs << "\n";
        }

        void DrawBody(color pixel_color, int samples_per_pixel) {
            auto r = pixel_color.x();
            auto g = pixel_color.y();
            auto b = pixel_color.z();

            // Replace NaN components with zero. See explanation in Ray Tracing: The Rest of Your Life.
            if (r != r) r = 0.0;
            if (g != g) g = 0.0;
            if (b != b) b = 0.0;

            // Divide the color by the number of samples and gamma-correct for gamma=2.0.
            auto scale = 1.0 / samples_per_pixel;
            r = sqrt(scale * r);
            g = sqrt(scale * g);
            b = sqrt(scale * b);

            // Write the translated [0,255] value of each color component.
            ofs << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
                << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
                << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
        }
    
    private:
        std::ofstream ofs;
};
