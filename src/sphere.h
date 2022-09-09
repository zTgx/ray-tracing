#pragma once

#include "utils.h"
#include "hitable.h"
#include "ray.h"

class sphere : public Hitable {
    public:
        sphere() {}
        sphere(Point center, double radius, std::shared_ptr<material> m)
            : center(center), radius(radius), mat_ptr(m) {};

        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
        {
            vec3 oc = r.GetOrigin() - center;
            auto a = r.GetDirection().length_squared();
            auto half_b = dot(oc, r.GetDirection());
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = half_b*half_b - a*c;
            if (discriminant < 0) return false;
            auto sqrtd = sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            auto root = (-half_b - sqrtd) / a;
            if (root < t_min || t_max < root) {
                root = (-half_b + sqrtd) / a;
                if (root < t_min || t_max < root)
                    return false;
            }

            rec.t = root;
            rec.p = r.At(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;

            return true;
        }

    private:
        Point center;
        double radius;
        std::shared_ptr<material> mat_ptr;
};