#ifndef RAY_TRACER_OBJECT_H
#define RAY_TRACER_OBJECT_H
#include "Intersection.h"
#include "Material.h"

class Object {
public:
    virtual ~Object() = default;

    virtual Vector normal_at(const Point &p) const = 0;

    virtual Material &getMaterial() = 0;

    virtual const Material &getMaterial() const = 0;

    // virtual bool operator==(const Object& other) const = 0;
};

#endif //RAY_TRACER_OBJECT_H