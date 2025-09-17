#ifndef RAY_TRACER_ENVIRONMENT_H
#define RAY_TRACER_ENVIRONMENT_H
#include "Vector.h"

class Environment {
    Vector gravity;
    Vector wind;

public:
    Environment(const Vector &gravity, const Vector &wind) : gravity(gravity), wind(wind) {
    }

    Vector getGravity() const {
        return gravity;
    }

    Vector getWind() const {
        return wind;
    }
};

#endif //RAY_TRACER_ENVIRONMENT_H
