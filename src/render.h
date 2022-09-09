#pragma once

#include "context.h"
#include "camera.h"
#include "world.h"
#include <iostream>

static const int samples_per_pixel = 10;
static const int max_depth = 50;

class Renderer
{
    public:
        static void Draw(Context* context, World* world)
        {
            const int image_height = context->GetHeight();
            const int image_width  = context->GetWidth();

            Camera* camera = context->GetCamera();

            for (int j = image_height-1; j >= 0; --j) {
                std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

                for (int i = 0; i < image_width; ++i) {
                    color pixel_color(0,0,0);
                    for (int s = 0; s < samples_per_pixel; ++s) {
                        auto u = (i + random_double()) / (image_width-1);
                        auto v = (j + random_double()) / (image_height-1);
                        
                        Ray r = camera->GetRay(u, v);
                        pixel_color += ray_color(r, world, max_depth);
                    }

                    context->Draw(pixel_color, samples_per_pixel);
                }
            }
        }
};