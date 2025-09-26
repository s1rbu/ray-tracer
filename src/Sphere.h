#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H
#include <vector>

#include "Ray.h"
#include "Object.h"
#include "Intersection.h"
#include "Material.h"

class Sphere : public Object {
    Matrix transform = Matrix::identity();
    Material material;

public:
    Sphere() {
    }

    explicit Sphere(const Object &obj) : Object(obj) {
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
        return this->transform == other.transform && material == other.material;
    }

    Matrix getTransform() const {
        return transform;
    }

    Material &getMaterial() override {
        return material;
    }

    const Material &getMaterial() const override { return material; }

    void setMaterial(const Material &material_) {
        this->material = material_;
    }

    void setTransform(const Matrix &other) {
        transform = other;
    }

    Vector normal_at(const Point &world_point) const override {
        const Point object_point = Point(Matrix::inverse(transform) * world_point);
        const Vector object_normal = object_point - Point(0, 0, 0);
        Vector world_normal = Vector(Matrix::transpose(Matrix::inverse(transform)) * object_normal);
        world_normal.setW(0);

        return Vector::normalize(world_normal);
    }
};

#endif //RAY_TRACER_SPHERE_H
