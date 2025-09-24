#ifndef RAY_TRACER_INTERSECTION_H
#define RAY_TRACER_INTERSECTION_H
#include "Object.h"

class Intersection {
    double t;
    const Object *object;

    public:
    Intersection(const double t_, const Object &object_) : t(t_), object(&object_) {}

    double getT() const {
        return t;
    }

    const Object& getObject() const {
        return *object;
    }

    bool operator==(const Intersection & other) const {
        return t == other.t && object == other.object;
    }
};

#endif //RAY_TRACER_INTERSECTION_H