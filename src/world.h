#pragma once

#include <memory>
#include <vector>

#include "utils.h"
#include "hitable.h"
#include "material.h"
#include "sphere.h"

/**
 * @brief 世界
 * 包含所有实现了 hitable 的对象
 */
class World : public Hitable  {
    public:
        World() {}
        World(std::shared_ptr<Hitable> object) { Add(object); }

    public:
        void Clear() { objects.clear(); }
        void Add(std::shared_ptr<Hitable> object) { objects.emplace_back(object); }

    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

    private:
        std::vector<std::shared_ptr<Hitable>> objects;
};

bool World::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    auto hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

World* NewWorld()
{
    World* world = new World;

    auto ground_material = std::make_shared<lambertian>(Color(0.5, 0.5, 0.5));
    world->Add(std::make_shared<sphere>(Point(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world->Add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world->Add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world->Add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5);
    world->Add(std::make_shared<sphere>(Point(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(Color(0.4, 0.2, 0.1));
    world->Add(std::make_shared<sphere>(Point(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<metal>(Color(0.7, 0.6, 0.5), 0.0);
    world->Add(std::make_shared<sphere>(Point(4, 1, 0), 1.0, material3));

    return world;
}