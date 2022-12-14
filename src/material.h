
#pragma once

#include "utils.h"
#include "vec3.h"
#include "ray.h"

struct HitResult;
class material {
    public:
        // Scatter -> 分散
        // attenuation -> 衰减
        // To reduce the intensity of light over the distance a light ray travels is generally called attenuation.
        virtual bool Scatter(const Ray& r_in, const HitResult& rec, Color& attenuation, Ray& scattered) const = 0;
};

// Lambertian反射(也叫理想散射) 漫反射
class lambertian : public material {
    public:
        lambertian(const Color& a) : albedo(a) {}

        virtual bool Scatter(const Ray& r_in, const HitResult& rec, Color& attenuation, Ray& scattered) const override 
        {
            auto scatter_direction = rec.normal + random_unit_vector();

            // Catch degenerate Scatter direction
            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;

            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    private:
        // 漫反射系数
        Color albedo;
};

// 金属反射
// Mirrored Light Reflection
class metal : public material {
    public:
        metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool Scatter(
            const Ray& r_in, const HitResult& rec, Color& attenuation, Ray& scattered
        ) const override {
            // b = v . n 
            // reflected = v - 2*dot(v,n)*n;
            vec3 reflected = reflect(unit_vector(r_in.GetDirection()), rec.normal);
            scattered = Ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;

            // 
            return (dot(scattered.GetDirection(), rec.normal) > 0);
        }

    private:
        Color albedo;
        double fuzz;
};

// 全反射
// 
class dielectric : public material {
    public:
        dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool Scatter(
            const Ray& r_in, const HitResult& rec, Color& attenuation, Ray& scattered
        ) const override {
            attenuation = Color(1.0, 1.0, 1.0);
            double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

            vec3 unit_direction = unit_vector(r_in.GetDirection());
            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            vec3 direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
                direction = reflect(unit_direction, rec.normal);
            else
                // 折射
                direction = refract(unit_direction, rec.normal, refraction_ratio);

            scattered = Ray(rec.p, direction);
            return true;
        }

    public:
        double ir; // Index of Refraction

    private:
        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
        }
};