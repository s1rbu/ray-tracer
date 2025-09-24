#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H
#include <vector>

#include "Ray.h"

class Sphere : public Object {
public:
    Sphere() {
    }

    static std::vector<Intersection> intersect(const Sphere &sphere, const Ray &ray) {
        const Vector sphereToRay = ray.getOrigin() - Point(0, 0, 0);

        const double a = Vector::dot(ray.getDirection(), ray.getDirection());
        const double b = 2 * Vector::dot(ray.getDirection(), sphereToRay);
        const double c = Vector::dot(sphereToRay, sphereToRay) - 1;

        const double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return {};
        }

        std::vector<Intersection> result;
        result.emplace_back((-b - sqrt(discriminant))/(2*a), sphere);
        result.emplace_back((-b + sqrt(discriminant))/(2*a), sphere);

        return result;
    }

    bool operator==(const Sphere &other) const {
        return true;
    }
};

#endif //RAY_TRACER_SPHERE_H
