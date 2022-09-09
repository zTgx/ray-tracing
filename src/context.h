#pragma once

#include "color.h"
#include "camera.h"
#include "render.h"

class Context
{
    public:
        Context(const float ratio, const int width, const int height) noexcept 
        {
            // setup camera
            point3 lookfrom(13,2,3);
            point3 lookat(0,0,0);
            vec3 vup(0,1,0);
            auto dist_to_focus = 10.0;
            auto aperture = 0.1;

            m_camera = new Camera(lookfrom, lookat, vup, 20, ratio, aperture, dist_to_focus);
            
            // setup render
            m_render = new Renderer(ratio, width, height);
        }
    
        ~Context() 
        {
            delete m_camera;
            m_camera = nullptr;

            delete m_render;
            m_render = nullptr;
        }

    public:
        void Render(World* world) { m_render->Draw(world, m_camera); }

    public:
        Camera* GetCamera() { return m_camera; }

    private:
        Camera* m_camera;
        Renderer* m_render;
};