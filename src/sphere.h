#pragma once

#include "utils.h"
#include "hitable.h"
#include "ray.h"

// 球体实例
// For a sphere, the normal is in the direction of the hitpoint minus the center:
// N = P - Center; points out

// (P−C)⋅(P−C)=r*r
//  If it does hit the sphere, there is some t for which P(t) satisfies the sphere equation. So we are looking for any t where this is true:
// So we are looking for any t where this is true:
// (P(t)−C)⋅(P(t)−C)=r*r
// 求t来判断是否相交
// t2b⋅b+2tb⋅(A−C)+(A−C)⋅(A−C)−r2=0
// => at*t + 2tb + c = 0
// 通过Δ＝b²－4ac，来判断是否有解。
class sphere : public Hitable {
    public:
        sphere() {}
        sphere(Point center, double radius, std::shared_ptr<material> m)
            : center(center), radius(radius), mat_ptr(m) {};

        // We want to
        // know if our ray p(t) = A + t*B ever hits the sphere anywhere. If it does hit the sphere,
        // there is some t for which p(t) satisfies the sphere equation.
        virtual bool hit(const Ray& r, double t_min, double t_max, HitResult& rec) const override
        {
            // ray 原点 到 球体原点的向量
            vec3 oc = r.GetOrigin() - center;

            // ray原点 和 到球体原点 dot
            // dot((p - C),(p - C)) = (y-cy)*(y-cy) + (z-cz)* (z-cz).
            // any point p that satisfies this equation is on the sphere
            // oc 在 direction 的投影长度
            auto half_b = dot(oc, r.GetDirection());

            // ray 的长度 平方
            auto a = r.GetDirection().length_squared();

            // 到 球心的长度平方 - 球体radius平方
            auto c = oc.length_squared() - radius*radius;

            auto discriminant = half_b*half_b - a*c;
            if (discriminant < 0) return false;

            {
                /**
                 * It gets uglier if the sphere center is at (cx, cy, cz):
                 *  (x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz)= R*R
                 * You might note that the vector from 
                 * center C = (cx,cy,cz) to point p = (x,y,z) is (p - C). 
                 * And dot((p - C),(p - C)) = (y-cy)*(y-cy) + (z-cz)*(z-cz).
                 * 
                 * 推到为：
                 * dot((p - c),(p - c)) = R*R
                 * We can read this as “any point p that satisfies this equation is on the sphere.
                 */
                // vec3 oc = r.GetOrigin() - center;
                // float a = dot(r.GetDirection(), r.GetDirection());
                // float b = 2.0 * dot(oc, r.GetDirection());
                // float c = dot(oc, oc) - radius * radius;

                // t2b⋅b+2tb⋅(A−C)+(A−C)⋅(A−C)−r2=0

                // float discriminant = b * b - 4 * a * c;
                // if (discriminant < 0) return false; // 不想交
            }

            // 有解的情况
            // x = [-b + sqrt(discri) ] / 2a or [ -b - sqrt(discri)] / 2a
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