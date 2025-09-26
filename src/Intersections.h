#ifndef RAY_TRACER_INTERSECTIONS_H
#define RAY_TRACER_INTERSECTIONS_H

#include <vector>
#include "Intersection.h"

template <typename... Is>
std::vector<Intersection> intersections(const Is&... args) {
    return std::vector<Intersection>{ args... };
}

inline const Intersection *hit(const std::vector<Intersection> &xs) {
    double min = std::numeric_limits<double>::max();
    const Intersection *minimum = nullptr;
    for (const auto &x : xs) {
        if (x.getT() < min && x.getT() >= 0) {
            min = x.getT();
            minimum = &x;
        }
    }

    return minimum;
}
#endif //RAY_TRACER_INTERSECTIONS_H