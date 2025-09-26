#ifndef RAY_TRACER_LIGHT_H
#define RAY_TRACER_LIGHT_H
#include "Color.h"
#include "Point.h"

class Light {
    Point position;
    Color intensity;

public:
    Light(const Point &position_, const Color &intensity_) : position(position_), intensity(intensity_) {
    }

    Point getPosition() const {
        return position;
    }

    Color getIntensity() const {
        return intensity;
    }
};

#endif //RAY_TRACER_LIGHT_H
