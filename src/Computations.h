#ifndef RAY_TRACER_COMPUTATIONS_H
#define RAY_TRACER_COMPUTATIONS_H
#include "Intersection.h"
#include "Object.h"
#include "Ray.h"

class Computations {
    double t = 0;
    const Object *object = nullptr;
    Point point;
    Vector eyeV;
    Vector normalV;
    bool inside = false;

public:
    Computations(const double t_, const Object *object_, const Point &point_,
                 const Vector &eyev_, const Vector &normalv_, const bool inside_)
        : t(t_), object(object_), point(point_), eyeV(eyev_), normalV(normalv_), inside(inside_) {
    }

    static Computations prepareComputations(const Intersection &i, const Ray &r) {
        const double t_ = i.getT();
        const Object *object_ = &i.getObject();

        const Point point_ = Ray::position(r, t_);
        const Vector eyeV_ = -r.getDirection();
        Vector normalV_ = object_->normal_at(point_);

        bool inside_ = false;
        if (Vector::dot(normalV_, eyeV_) < 0) {
            inside_ = true;
            normalV_ = -normalV_;
        } else {
            inside_ = false;
        }

        return {t_, object_, point_, eyeV_, normalV_, inside_};
    }

    double getT() const { return t; }
    const Object *getObject() const { return object; }
    const Point &getPoint() const { return point; }
    const Vector &getEyeV() const { return eyeV; }
    const Vector &getNormalV() const { return normalV; }

    bool getInside() const {
        return inside;
    }
};

#endif //RAY_TRACER_COMPUTATIONS_H
