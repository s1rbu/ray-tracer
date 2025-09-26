#ifndef RAY_TRACER_VECTOR_H
#define RAY_TRACER_VECTOR_H
#include "Tuple.h"

class Point;

class Vector : public Tuple {
public:
    Vector(const double x, const double y, const double z) : Tuple(x, y, z, 0.0) {
    }

    explicit Vector(const Tuple &tuple) : Tuple(tuple) {
    }

    Vector operator+(const Vector &other) const {
        return {
            getX() + other.getX(),
            getY() + other.getY(),
            getZ() + other.getZ()
        };
    }

    Point operator+(const Point &p) const;

    Vector operator-(const Vector &other) const {
        return {
            getX() - other.getX(),
            getY() - other.getY(),
            getZ() - other.getZ()
        };
    }

    Vector operator-() const {
        return {-getX(), -getY(), -getZ()};
    }

    static double magnitude(const Vector &v) {
        return sqrt(pow(v.getX(), 2) + pow(v.getY(), 2) + pow(v.getZ(), 2) + pow(v.getW(), 2));
    }

    static Vector normalize(const Vector &v) {
        const double m = magnitude(v);
        return {v.getX() / m, v.getY() / m, v.getZ() / m};
    }

    static double dot(const Vector &v1, const Vector &v2) {
        return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
    }

    static Vector cross(const Vector &v1, const Vector &v2) {
        return {
            v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
            v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
            v1.getX() * v2.getY() - v1.getY() * v2.getX()
        };
    }

    static Vector reflect(const Vector &in, const Vector &normal) {
        return in - Vector(normal * 2 * Vector::dot(in, normal));
    }
};

#endif //RAY_TRACER_VECTOR_H
