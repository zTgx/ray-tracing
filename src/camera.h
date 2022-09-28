#pragma once

#include "utils.h"

struct CameraProps
{
    Point FROM{0, 0, -1};
    Point AT{0, 0, 0};
    Point vup{0, 1, 0};
    float vfov{40}; // vertical field-of-view in degrees
    float aspect_ratio{1};
    float aperture{0};
    float focus_dist{10};
};

class Camera {
    public:
        Camera(
            Point FROM,
            Point AT,
            Point vup,
            float vfov, // vertical field-of-view in degrees
            float aspect_ratio,
            float aperture,
            float focus_dist
        ) {
            // to radians
            auto theta = degrees_to_radians(vfov);

            // tan(theta/2) = t / |n|;
            /***
             *  
             * ◺
             * 
             * */
            auto h = tan(theta/2);

            // view port screen
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;


            w = unit_vector(FROM - AT);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = FROM;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

            lens_radius = aperture / 2;
        }

        Ray GetRay(float s, float t) const 
        {
            Point rd = lens_radius * random_in_unit_disk();
            Point offset = u * rd.x() + v * rd.y();
            
            return Ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
        }

        void Update(Point from, Point at, Point vup, const float vfov, const float ratio, const float aperture, const float distToFocus)
        {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = ratio * viewport_height;

            w = unit_vector(from - at);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = from;
            horizontal = distToFocus * viewport_width * u;
            vertical = distToFocus * viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - distToFocus * w;

            lens_radius = aperture / 2;
        }

    private:
        Point origin;
        Point lower_left_corner;
        Point horizontal;
        Point vertical;
        Point u, v, w;

        float lens_radius;
        // CameraProps props;
};