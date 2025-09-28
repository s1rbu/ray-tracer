#ifndef RAY_TRACER_WORLD_H
#define RAY_TRACER_WORLD_H
#include <list>

#include "Computations.h"
#include "Intersections.h"
#include "Light.h"
#include "Point.h"
#include "Sphere.h"

class World {
    Light light;
    std::vector<Sphere> spheres{Sphere(), Sphere()};

public:
    World() : light(Light(Point(-10, 10, -10), Color(1, 1, 1))) {
        spheres[0].getMaterial().setSurfaceColor(Color(0.8, 1.0, 0.6));
        spheres[0].getMaterial().setDiffuse(0.7);
        spheres[0].getMaterial().setSpecular(0.2);
        spheres[1].setTransform(Matrix::scaling(0.5, 0.5, 0.5));
    }

    Light getLight() const {
        return light;
    }

    void setLight(const Light &light_) {
        this->light = light_;
    }

    std::vector<Sphere> &getSpheres() { return spheres; }
    const std::vector<Sphere> &getSpheres() const { return spheres; }


    std::vector<Intersection> intersectWorld(const Ray &r) const {
        std::vector<Intersection> xs;
        for (const auto &sphere: spheres) {
            std::vector<Intersection> sphereHits = Sphere::intersect(sphere, r);
            xs.insert(xs.end(), sphereHits.begin(), sphereHits.end());
        }

        std::sort(xs.begin(), xs.end());
        return xs;
    }

    static Color shadeHit(const World &world, const Computations &comps) {
        return Material::lighting(comps.getObject()->getMaterial(), world.getLight(), comps.getPoint(), comps.getEyeV(),
                                  comps.getNormalV());
    }

    static Color colorAt(const World &world, const Ray &r) {
        auto xs = world.intersectWorld(r);
        const Intersection *h = hit(xs);
        if (!h) {
            return Color(0, 0, 0);
        }

        Computations comps = Computations::prepareComputations(*h, r);

        return World::shadeHit(world, comps);
    }
};

#endif //RAY_TRACER_WORLD_H
