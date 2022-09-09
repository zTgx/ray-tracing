#pragma once

#include "ppm.h"
#include "color.h"
#include "camera.h"

class Context
{
    public:
        Context(const float ratio, const int width, const int height) noexcept 
        {
            m_ratio  = ratio;
            m_width  = width;
            m_height = height;

            // setup ppm
            m_ppm = new PPM(width, height);

            // setup camera
            point3 lookfrom(13,2,3);
            point3 lookat(0,0,0);
            vec3 vup(0,1,0);
            auto dist_to_focus = 10.0;
            auto aperture = 0.1;

            m_camera = new Camera(lookfrom, lookat, vup, 20, m_ratio, aperture, dist_to_focus);

        }
    
    public:
        void Draw(color pixel_color, int samples_per_pixel) { m_ppm->DrawBody(pixel_color, samples_per_pixel);}
    
    public:
        const int GetHeight() const { return m_height; }
        const int GetWidth()  const { return m_width; }
        Camera* GetCamera() { return m_camera; }
    private:
        float m_ratio;
        int m_width;
        int m_height;

        PPM* m_ppm;
        Camera* m_camera;
};