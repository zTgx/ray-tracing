#pragma once

#include "vec3.h"

class Ray {
    public:
        Ray() {}
        Ray(const Point& origin, const Point& direction): m_origin(origin), m_direction(direction){}

    public:
        Point GetOrigin()    const { return m_origin; }
        Point GetDirection() const { return m_direction; }

        // The direction is the current position + the direction vector we just defined.
        // looking at the target direction
        Point At(float t)    const { return m_origin + t * m_direction; }

    private:
        Point m_origin;
        Point m_direction;
};
