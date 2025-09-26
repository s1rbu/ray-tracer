#ifndef RAY_TRACER_COLOR_H
#define RAY_TRACER_COLOR_H
#include "Tuple.h"

class Color : public Tuple {
public:
    Color() {
    }

    Color(const double red, const double green, const double blue) : Tuple(red, green, blue, 0.0) {
    }

    explicit Color(const Tuple &tuple) : Tuple(tuple) {
    }

    double red() const {
        return getX();
    }

    double green() const {
        return getY();
    }

    double blue() const {
        return getZ();
    }

    static Color hadamard(const Color &c1, const Color &c2) {
        return {c1.red() * c2.red(), c1.green() * c2.green(), c1.blue() * c2.blue()};
    }
};

#endif //RAY_TRACER_COLOR_H
