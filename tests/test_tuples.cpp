#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Point.h"
#include "Tuple.h"
#include "Vector.h"

TEST_CASE("A tuple with w=1.0 is a point") {
    Tuple a(4.3, -4.2, 3.1, 1.0);

    REQUIRE(a.getX() == Approx(4.3));
    REQUIRE(a.getY() == Approx(-4.2));
    REQUIRE(a.getZ() == Approx(3.1));
    REQUIRE(a.getW() == Approx(1.0));

    REQUIRE(a.isPoint());
    REQUIRE_FALSE(a.isVector());
}

TEST_CASE("A tuple with w=0 is a vector") {
    Tuple a(4.3, -4.2, 3.1, 0.0);

    REQUIRE(a.getX() == Approx(4.3));
    REQUIRE(a.getY() == Approx(-4.2));
    REQUIRE(a.getZ() == Approx(3.1));
    REQUIRE(a.getW() == Approx(0.0));

    REQUIRE(a.isVector());
    REQUIRE_FALSE(a.isPoint());
}

TEST_CASE("point() creates tuples with w=1") {
    const Tuple *p = new Point(4, -4, 3);

    REQUIRE(*p == Tuple(4, -4, 3, 1));

    delete p;
}

TEST_CASE("vector() creates tuples with w=0") {
    const Tuple *v = new Vector(4, -4, 3);

    REQUIRE(*v == Tuple(4, -4, 3, 0));

    delete v;
}

TEST_CASE("Adding two tuples") {
    const Tuple a1(3, -2, 5, 1);
    const Tuple a2(-2, 3, 1, 0);

    REQUIRE(a1+a2 == Tuple(1,1,6,1));
}

TEST_CASE("Operator += adding two tuples") {
    Tuple a1(3, -2, 5, 1);
    const Tuple a2(-2, 3, 1, 0);

    a1 += a2;

    REQUIRE(a1 == Tuple(1,1,6,1));
}

TEST_CASE("Point+Vector=Point") {
    Point p(4, -4, 3);
    const Vector v(4, -4, 3);

    p += v;
    REQUIRE(p == Point(8,-8,6));
}

TEST_CASE("Subtracting two points") {
    const Point p1(3, 2, 1);
    const Point p2(5, 6, 7);

    REQUIRE(p1-p2 == Vector(-2,-4,-6));
}

TEST_CASE("Subtracting a vector from a point") {
    const Point p(3, 2, 1);
    const Vector v(5, 6, 7);

    REQUIRE(p-v == Point(-2,-4,-6));
}

TEST_CASE("Subtracting two vectors") {
    const Vector v1(3, 2, 1);
    const Vector v2(5, 6, 7);

    REQUIRE(v1-v2 == Vector(-2,-4,-6));
}

TEST_CASE("Subtracting a vector from the zero vector") {
    const Vector zero(0, 0, 0);
    const Vector v(1, -2, 3);

    REQUIRE(zero-v == Vector(-1,2,-3));
}

TEST_CASE("Negating") {
    const Tuple t(-1, -2, 3, -4);
    const Vector v(1, -2, 3);
    const Point p(-2, 1, -3);

    REQUIRE(-t == Tuple(1,2,-3,4));
    REQUIRE(-v == Vector(-1,2,-3));
    REQUIRE(-p == Point(2,-1,3));
}

TEST_CASE("Multiplying a tuple by a scalar") {
    Tuple a(1, -2, 3, -4);
    a = a * 3.5;

    REQUIRE(a == Tuple(3.5, -7, 10.5, -14));
}

TEST_CASE("Multiplying a tuple by a fraction") {
    Tuple a(1, -2, 3, -4);
    a = a * 0.5;

    REQUIRE(a == Tuple(0.5, -1, 1.5, -2));
}

TEST_CASE("Dividing a tuple by a scalar") {
    Tuple a(1, -2, 3, -4);
    a = a / 2;

    REQUIRE(a == Tuple(0.5, -1, 1.5, -2));
}

TEST_CASE("Computing the magnitude of vector(1, 0, 0)") {
    const Vector v(1, 0, 0);

    REQUIRE(Vector::magnitude(v) == 1);
}

TEST_CASE("Computing the magnitude of vector(0, 1, 0)") {
    const Vector v(0, 1, 0);

    REQUIRE(Vector::magnitude(v) == 1);
}

TEST_CASE("Computing the magnitude of vector(0, 0, 1)") {
    const Vector v(0, 0, 1);

    REQUIRE(Vector::magnitude(v) == 1);
}

TEST_CASE("Computing the magnitude of vector(1, 2, 3)") {
    const Vector v(1, 2, 3);

    REQUIRE(Vector::magnitude(v) == sqrt(14));
}

TEST_CASE("Computing the magnitude of vector(-1, -2, -3)") {
    const Vector v(-1, -2, -3);

    REQUIRE(Vector::magnitude(v) == sqrt(14));
}

TEST_CASE("Normalizing vector(4, 0, 0) gives (1, 0, 0)") {
    const Vector v(4, 0, 0);

    REQUIRE(Vector::normalize(v) == Vector(1, 0, 0));
}

TEST_CASE("Normalizing vector(1, 2, 3)") {
    const Vector v(1, 2, 3);

    REQUIRE(Vector::normalize(v) == Vector(0.26726, 0.53452, 0.80178));
}

TEST_CASE("The magnitude of a normalized vector") {
    const Vector v(1, 2, 3);
    const Vector norm = Vector::normalize(v);

    REQUIRE(Vector::magnitude(norm) == 1);
}

TEST_CASE("The dot product of two tuples") {
    const Vector v1(1, 2, 3);
    const Vector v2(2, 3, 4);

    REQUIRE(Vector::dot(v1, v2) == 20);
}

TEST_CASE("The cross product of two vectors") {
    const Vector v1(1, 2, 3);
    const Vector v2(2, 3, 4);

    REQUIRE(Vector::cross(v1, v2) == Vector(-1, 2, -1));
    REQUIRE(Vector::cross(v2, v1) == Vector(1,-2,1));
}
