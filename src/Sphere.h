#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H
#include <vector>

#include "Ray.h"
#include "Object.h"
#include "Intersection.h"

class Sphere : public Object {
    Matrix transform = Matrix::identity();

public:
    Sphere() {
    }

    static std::vector<Intersection> intersect(const Sphere &sphere, const Ray &ray) {
        const Ray ray2 = Ray::transform(ray, Matrix::inverse(sphere.getTransform()));
        const Vector sphereToRay = ray2.getOrigin() - Point(0, 0, 0);

        const double a = Vector::dot(ray2.getDirection(), ray2.getDirection());
        const double b = 2 * Vector::dot(ray2.getDirection(), sphereToRay);
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

    Matrix getTransform() const {
        return transform;
    }

    void setTransform(const Matrix &other) {
        transform = other;
    }

    static Vector normal_at(const Sphere &sphere, const Point &world_point) {
        const Point object_point = Point(Matrix::inverse(sphere.transform) * world_point);
        const Vector object_normal = object_point - Point(0, 0, 0);
        Vector world_normal = Vector(Matrix::transpose(Matrix::inverse(sphere.transform)) * object_normal);
        world_normal.setW(0);

        return Vector::normalize(world_normal);
    }
};

#endif //RAY_TRACER_SPHERE_H
