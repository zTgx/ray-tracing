#pragma once

#include "vec3.h"

class Ray {
    public:
        Ray() {}
        Ray(const Point& origin, const vec3& direction): orig(origin), dir(direction), tm(0){}
        Ray(const Point& origin, const vec3& direction, double time): orig(origin), dir(direction), tm(time){}

        Point  origin()        const { return orig; }
        Point  at(double t)    const { return orig + t*dir; }
        vec3    direction()     const { return dir; }
        double  time()          const { return tm; }

    public:
        Point orig;
        vec3   dir;
        double tm;
};
