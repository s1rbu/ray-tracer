#ifndef RAY_TRACER_POINT_H
#define RAY_TRACER_POINT_H
#include "Tuple.h"
#include "Vector.h"

class Point : public Tuple {
public:
    Point(const double x, const double y, const double z) : Tuple(x, y, z, 1.0) {
    }

    Point operator+(const Vector &other) const {
        return {
            getX() + other.getX(),
            getY() + other.getY(),
            getZ() + other.getZ()
        };
    }

    Point &operator+=(const Vector &other) {
        Tuple::operator+=(other);
        return *this;
    }

    Point operator-(const Vector &other) const {
        return {
            getX() - other.getX(),
            getY() - other.getY(),
            getZ() - other.getZ()
        };
    }

    Vector operator-(const Point &other) const {
        return {
            getX() - other.getX(),
            getY() - other.getY(),
            getZ() - other.getZ()
        };
    }

    Point operator-() const {
        return {-getX(), -getY(), -getZ()};
    }
};

#endif //RAY_TRACER_POINT_H
