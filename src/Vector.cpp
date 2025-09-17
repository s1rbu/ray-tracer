#include "Point.h"
#include "Vector.h"

Point Vector::operator+(const Point &p) const {
    return {
        getX() + p.getX(),
        getY() + p.getY(),
        getZ() + p.getZ()
    };
}
