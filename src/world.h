#pragma once

#include <memory>
#include <vector>

#include "utils.h"
#include "hittable.h"
#include "material.h"
#include "sphere.h"

class World : public hittable  {
    public:
        World() {}
        World(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(
            const Ray& r, double t_min, double t_max, hit_record& rec) const override;
    public:
        std::vector<shared_ptr<hittable>> objects;
};

bool World::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
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

    auto ground_material = make_shared<lambertian>(Color(0.5, 0.5, 0.5));
    world->add(make_shared<sphere>(Point(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world->add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world->add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world->add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world->add(make_shared<sphere>(Point(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(Color(0.4, 0.2, 0.1));
    world->add(make_shared<sphere>(Point(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(Color(0.7, 0.6, 0.5), 0.0);
    world->add(make_shared<sphere>(Point(4, 1, 0), 1.0, material3));

    return world;
}