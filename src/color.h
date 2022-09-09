#pragma once

#include "ray.h"
#include "hittable.h"
#include "material.h"

color ray_color(const Ray& r, const hittable* world, int depth) {
    hit_record rec;

    // If we've exceeded the Ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    if (world->hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}
