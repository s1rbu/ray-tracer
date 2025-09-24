#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H
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
};

#endif //RAY_TRACER_RAY_H
