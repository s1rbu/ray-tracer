#ifndef RAY_TRACER_PROJECTILE_H
#define RAY_TRACER_PROJECTILE_H
#include "Environment.h"
#include "Point.h"

class Projectile {
    Point position;
    Vector velocity;

public:
    Projectile(const Point &position, const Vector &velocity) : position(position), velocity(velocity) {
    }

    static Projectile tick(const Environment &env, const Projectile &proj) {
        const Point position = proj.position + proj.velocity;
        const Vector velocity = proj.velocity + env.getGravity() + env.getWind();

        return {position, velocity};
    }

    Point getPosition() const {
        return position;
    }
};

#endif //RAY_TRACER_PROJECTILE_H
