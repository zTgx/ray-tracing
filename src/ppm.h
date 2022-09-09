#pragma once

#include <fstream>
#include "vec3.h"

// http://users.csc.calpoly.edu/~akeen/courses/csc101/handouts/assignments/ppmformat.html#:~:text=The%20ppm%20P3%20format%20is,pixel%20in%20the%20next%20row).
// The header consists of :
// the characters P3, 
// the integer width of the image (in pixels), 
// the integer height of the image, 
// and the maximum value for a Color component (we will use 255 for this value).
class PPM
{
    public:
        PPM(const float ratio, const int width, const int height) noexcept 
        { 
            m_width     = width;
            m_height    = height;  
            m_ratio     = ratio;

            m_ofs.open ("ppm.ppm"); 
            DrawHeader(width, height);
        }

    private:
        /** Header Format:
         * P3
         * width height
         * 255
         */
        void DrawHeader(const int width, const int height) { 
            m_ofs << "P3\n"; 
            m_ofs << width << " " << height << "\n"; 
            m_ofs << "255";
            m_ofs << "\n";
        }

    public:
        void DrawBody(Color pixel_color, int samples_per_pixel) {
            auto r = pixel_color.x();
            auto g = pixel_color.y();
            auto b = pixel_color.z();

            // Replace NaN components with zero. See explanation in Ray Tracing: The Rest of Your Life.
            if (r != r) r = 0.0;
            if (g != g) g = 0.0;
            if (b != b) b = 0.0;

            // Divide the Color by the number of samples and gamma-correct for gamma=2.0.
            auto scale = 1.0 / samples_per_pixel;
            r = sqrt(scale * r);
            g = sqrt(scale * g);
            b = sqrt(scale * b);

            // Write the translated [0,255] value of each Color component.
            m_ofs << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
                << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
                << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
        }
    
    public:
        const int GetWidth()  { return m_width; }
        const int GetHeight() { return m_height; }
        const int GetRatio() { return m_ratio; }

    private:
        std::ofstream m_ofs;

        int m_width;
        int m_height;
        float m_ratio;
};
