#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H
#include "Matrix.h"
#include "Point.h"

class Ray {
    Point origin;
    Vector direction;

public:
    Ray(const Point &origin_, const Vector &direction_) : origin(origin_), direction(direction_) {
    }

    Point getOrigin() const {
        return origin;
    }

    Vector getDirection() const {
        return direction;
    }

    static Point position(const Ray &r, const double t) {
        return r.origin + Vector(r.direction * t);
    }

    static Ray transform(const Ray &r, const Matrix &m) {
        const Point p(m * r.origin);
        const Vector v(m * r.direction);

        return Ray(p, v);
    }
};

#endif //RAY_TRACER_RAY_H
