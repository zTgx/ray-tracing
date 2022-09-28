#pragma once

#include "vec3.h"

/**
 * @brief 计算向量长度
 * 
 * a ray as a function p(t) = A + t*B. Here p is a 3D position
 * along a line in 3D. A is the ray origin and B is the ray direction. The ray parameter t is a
 * real number (float in the code).
 * 
 */
class Ray {
    public:
        Ray() {}
        Ray(const Point& origin, const Point& direction): m_origin(origin), m_direction(direction){}

    public:
        Point GetOrigin()    const { return m_origin; }
        Point GetDirection() const { return m_direction; }

        // The direction is the current position + the direction vector we just defined.
        // looking at the target direction
        // Plug in a different t and p(t) moves the point along the ray.
        Point At(float t)    const { return m_origin + t * m_direction; }

    private:
        Point m_origin;
        Point m_direction;
};
