#include "catch.hpp"
#include "Computations.h"
#include "Ray.h"
#include "Sphere.h"

TEST_CASE("Precomputing the state of an intersection") {
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere shape;
    Intersection i(4, shape);
    Computations comps = Computations::prepareComputations(i, r);

    REQUIRE(comps.getT() == i.getT());
    REQUIRE(comps.getObject() == &i.getObject());
    REQUIRE(comps.getPoint() == Point(0,0,-1));
    REQUIRE(comps.getEyeV() == Vector(0,0,-1));
    REQUIRE(comps.getNormalV() == Vector(0,0,-1));
}

TEST_CASE("The hit, when an intersection occurs on the outside") {
    const Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    const Sphere shape;
    const Intersection i(4, shape);
    const Computations comps = Computations::prepareComputations(i, r);

    REQUIRE(comps.getInside() == false);
}

TEST_CASE("The hit, when an intersection occurs on the inside") {
    const Ray r(Point(0, 0, 0), Vector(0, 0, 1));
    const Sphere shape;
    const Intersection i(1, shape);
    const Computations comps = Computations::prepareComputations(i, r);

    REQUIRE(comps.getPoint() == Point(0,0,1));
    REQUIRE(comps.getEyeV() == Vector(0,0,-1));
    REQUIRE(comps.getInside() == true);
    REQUIRE(comps.getNormalV() == Vector(0,0,-1));
}
