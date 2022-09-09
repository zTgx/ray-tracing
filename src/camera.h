#pragma once

#include "utils.h"

struct CameraProps
{
    Point lookfrom{0, 0, -1};
    Point lookat{0, 0, 0};
    vec3  vup{0, 1, 0};
    float vfov{40}; // vertical field-of-view in degrees
    float aspect_ratio{1};
    float aperture{0};
    float focus_dist{10};
};

class Camera {
    public:
        Camera(
            Point lookfrom,
            Point lookat,
            vec3  vup,
            float vfov, // vertical field-of-view in degrees
            float aspect_ratio,
            float aperture,
            float focus_dist
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

            lens_radius = aperture / 2;
        }

        Ray GetRay(float s, float t) const {
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();
            return Ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
        }

        void Update(Point from, Point at, vec3 vup, const float vfov, const float ratio, const float aperture, const float distToFocus)
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