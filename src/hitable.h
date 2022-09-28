#pragma once

#include "vec3.h"
#include "ray.h"

class material;
struct HitResult {
    Point p;
    vec3 normal;
    std::shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    // If the ray and the normal face in the same direction, the ray is inside the object, 
    // if the ray and the normal face in the opposite direction, then the ray is outside the object. 
    // This can be determined by taking the dot product of the two vectors
    inline void SetFaceNormal(const Ray& r, const vec3& outward_normal) {
        front_face = dot(r.GetDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class Hitable {
    public:
        virtual bool OnHit(const Ray& r, double t_min, double t_max, HitResult& rec) const = 0;
};
