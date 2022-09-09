#pragma once

#include "color.h"
#include "camera.h"
#include "render.h"
#include "props.h"

class Context
{
    public:
        Context(const Props& p) noexcept 
        {
            // setup camera
            Point lookfrom(13,2,3);
            Point lookat(0,0,0);
            Point vup(0,1,0);
            float dist_to_focus = 10.0;
            float aperture = 0.1;

            m_camera = new Camera(lookfrom, lookat, vup, 40, p.ratio, aperture, dist_to_focus);
            
            // setup render
            m_render = new Renderer(p.ratio, p.width, p.height);
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
        void UpdateCamera(Point from, Point at, vec3 viewUp, const float vfov, const float ratio, const float aperture, const float distToFocus)
        {
            m_camera->Update(from, at, viewUp, vfov, ratio, aperture, distToFocus);
        }

    private:
        Camera* m_camera;
        Renderer* m_render;
};