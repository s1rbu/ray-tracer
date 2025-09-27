#include "catch.hpp"
#include "Light.h"
#include "Sphere.h"
#include "World.h"

TEST_CASE("The default world") {
    World w;

    REQUIRE(w.getLight().getPosition() == Point(-10, 10, -10));
    REQUIRE(w.getLight().getIntensity() == Color(1, 1, 1));

    const auto &spheres = w.getSpheres();
    REQUIRE(spheres.size() == 2);

    REQUIRE(spheres[0].getMaterial().getSurfaceColor() == Color(0.8, 1.0, 0.6));
    REQUIRE(spheres[0].getMaterial().getDiffuse() == 0.7);
    REQUIRE(spheres[0].getMaterial().getSpecular() == 0.2);

    REQUIRE(spheres[1].getTransform() == Matrix::scaling(0.5, 0.5, 0.5));
}

TEST_CASE("Intersect a world with a ray") {
    World w;
    Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    std::vector<Intersection> xs = w.intersectWorld(r);

    REQUIRE(xs.size() == 4);
    REQUIRE(xs[0].getT() == 4);
    REQUIRE(xs[1].getT() == 4.5);
    REQUIRE(xs[2].getT() == 5.5);
    REQUIRE(xs[3].getT() == 6);
}

TEST_CASE("Shading an intersection") {
    const World w;
    const Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    const Sphere shape = w.getSpheres()[0];
    const Intersection i(4,shape);
    const Computations comps = Computations::prepareComputations(i, r);
    const Color c = World::shadeHit(w, comps);

    REQUIRE(c == Color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("Shading an intersection from the inside") {
    World w;
    w.setLight(Light(Point(0,0.25,0), Color(1,1,1)));
    const Ray r(Point(0, 0, 0), Vector(0, 0, 1));
    const Sphere shape = w.getSpheres()[1];
    const Intersection i(0.5,shape);
    const Computations comps = Computations::prepareComputations(i, r);
    const Color c = World::shadeHit(w, comps);

    REQUIRE(c == Color(0.90498, 0.90498, 0.90498));
}

TEST_CASE("The color when a ray misses") {
    const World w;
    const Ray r(Point(0, 0, -5), Vector(0, 1, 0));
    const Color c = World::colorAt(w, r);

    REQUIRE(c == Color(0,0,0));
}

TEST_CASE("The color when a ray hits") {
    const World w;
    const Ray r(Point(0, 0, -5), Vector(0, 0,1));
    const Color c = World::colorAt(w, r);

    REQUIRE(c == Color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("The color with an intersection behind the ray") {
    World w;
    Sphere &outer = w.getSpheres()[0];
    outer.getMaterial().setAmbient(1);

    Sphere &inner = w.getSpheres()[1];
    inner.getMaterial().setAmbient(1);

    const Ray r(Point(0,0,0.75), Vector(0,0,-1));
    const Color c = World::colorAt(w, r);

    REQUIRE(c == inner.getMaterial().getSurfaceColor());
}