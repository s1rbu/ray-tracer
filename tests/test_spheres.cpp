#include "catch.hpp"
#include "Sphere.h"

TEST_CASE("The normal on a sphere at a point on the x axis") {
    const Sphere s;
    const Vector n = Sphere::normal_at(s, Point(1, 0, 0));

    REQUIRE(n == Vector(1,0,0));
}

TEST_CASE("The normal on a sphere at a point on the y axis") {
    const Sphere s;
    const Vector n = Sphere::normal_at(s, Point(0, 1, 0));

    REQUIRE(n == Vector(0,1,0));
}

TEST_CASE("The normal on a sphere at a point on the z axis") {
    const Sphere s;
    const Vector n = Sphere::normal_at(s, Point(0, 0, 1));

    REQUIRE(n == Vector(0,0,1));
}

TEST_CASE("The normal on a sphere at a nonaxial point") {
    const Sphere s;
    const Vector n = Sphere::normal_at(s, Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

    REQUIRE(n == Vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
}

TEST_CASE("The normal is a normalized vector") {
    const Sphere s;
    const Vector n = Sphere::normal_at(s, Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

    REQUIRE(n == Vector::normalize(n));
}

TEST_CASE("Computing the normal on a translated sphere") {
    Sphere s;
    s.setTransform(Matrix::translation(0, 1, 0));
    const Vector n = Sphere::normal_at(s, Point(0, 1.70711, -0.70711));

    REQUIRE(n == Vector(0, 0.70711, -0.70711));
}

TEST_CASE("Computing the normal on a transformed sphere") {
    Sphere s;
    const Matrix m = Matrix::scaling(1, 0.5, 1) * Matrix::rotationZ(std::numbers::pi / 5);
    s.setTransform(m);
    const Vector n = Sphere::normal_at(s, Point(0, sqrt(2) / 2, -sqrt(2) / 2));

    REQUIRE(n == Vector(0, 0.97014, -0.24254));
}
