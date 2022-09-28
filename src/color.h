#pragma once

#include "ray.h"
#include "hitable.h"
#include "material.h"

// At the core of a ray tracer is
// to send rays through pixels and compute what color is seen in the direction of those rays.
// This is of the form calculate which ray goes from the eye to a pixel, compute what that ray
// intersects, and compute a color for that intersection point.
// 计算 Ray r 经过的像素点的颜色
Color RayColor(const Ray& r, const Hitable* obj, int depth) {
    HitResult Result;

    // If we've exceeded the Ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Color(0,0,0);

    // 碰撞
    if (obj->hit(r, 0.001, INFINITY, Result)) {
        Ray ray;
        Color attenuation; 

        // 递归计算反射
        if (Result.mat_ptr->scatter(r, Result, attenuation, ray))
            return attenuation * RayColor(ray, obj, depth-1);

        return Color(0,0,0);
    }

    // 直射
    vec3 unit_direction = unit_vector(r.GetDirection());

    // blend
    // blendedValue=(1−t)⋅startValue+t⋅endValue,
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}
