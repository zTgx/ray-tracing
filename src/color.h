#pragma once

#include "ray.h"
#include "hitable.h"
#include "material.h"

Color RayColor(const Ray& r, const Hitable* obj, int depth) {
    HitRecord rec;

    // If we've exceeded the Ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0,0,0);

    if (obj->hit(r, 0.001, INFINITY, rec)) {
        Ray scattered;
        Color attenuation;

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * RayColor(scattered, obj, depth-1);

        return Color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.GetDirection());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}
