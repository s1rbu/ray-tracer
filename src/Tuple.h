#ifndef RAY_TRACER_TUPLE_H
#define RAY_TRACER_TUPLE_H

#include <cmath>
#include <iostream>

static constexpr double EPSILON = 1e-5;

class Tuple {
    double x, y, z, w;

public:
    Tuple(const double x_, const double y_, const double z_, const double w_) : x(x_), y(y_), z(z_), w(w_) {
    }

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    double getZ() const {
        return z;
    }

    double getW() const {
        return w;
    }

    bool isPoint() const {
        return w == 1.0;
    }

    bool isVector() const {
        return w == 0.0;
    }

    bool operator==(const Tuple &other) const {
        return (std::fabs(x - other.x) < EPSILON) &&
               (std::fabs(y - other.y) < EPSILON) &&
               (std::fabs(z - other.z) < EPSILON) &&
               (std::fabs(w - other.w) < EPSILON);
    }

    Tuple operator+(const Tuple &other) const {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }

    Tuple &operator+=(const Tuple &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Tuple operator-(const Tuple &other) const {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }

    Tuple operator-() const {
        return {-x, -y, -z, -w};
    }

    Tuple operator*(const double other) const {
        return {x * other, y * other, z * other, w * other};
    }

    Tuple operator/(const double other) const {
        return {x / other, y / other, z / other, w / other};
    }

    // Tuple operator*(const Tuple &other) const {
    //     return {x * other.x, y * other.y, z * other.z, w * other.w};
    // }

    friend std::ostream &operator<<(std::ostream &os, const Tuple &tuple) {
        if (tuple.isPoint()) {
            os << "Point: " << tuple.x << " " << tuple.y << " " << tuple.z << " " << tuple.w;
        } else if (tuple.isVector()) {
            os << "Vector: " << tuple.x << " " << tuple.y << " " << tuple.z << " " << tuple.w;
        } else {
            os << "Tuple: " << tuple.x << " " << tuple.y << " " << tuple.z << " " << tuple.w;
        }

        return os;
    }
};

#endif //RAY_TRACER_TUPLE_H
