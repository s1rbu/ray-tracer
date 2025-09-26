#ifndef RAY_TRACER_OBJECT_H
#define RAY_TRACER_OBJECT_H
#include "Material.h"

class Object {
public:
    virtual Vector normal_at(const Point &p) const = 0;

    virtual Material &getMaterial() = 0;

    virtual const Material &getMaterial() const = 0;
};

#endif //RAY_TRACER_OBJECT_H