#include "catch.hpp"
#include "Intersection.h"
#include "Intersections.h"
#include "Ray.h"
#include "Sphere.h"

TEST_CASE("Creating and querying a ray") {
    const Point origin(1,2,3);
    const Vector direction(4,5,6);
    const Ray ray(origin, direction);

    REQUIRE(ray.getOrigin() == origin);
    REQUIRE(ray.getDirection() == direction);
}

TEST_CASE("Computing a point from a distance") {
    const Ray r(Point(2,3,4), Vector(1,0,0));

    REQUIRE(Ray::position(r, 0) == Point(2,3,4));
    REQUIRE(Ray::position(r, 1) == Point(3,3,4));
    REQUIRE(Ray::position(r, -1) == Point(1,3,4));
    REQUIRE(Ray::position(r, 2.5) == Point(4.5,3,4));
}

TEST_CASE("A ray intersects a sphere at two points") {
    const Ray r(Point(0,0,-5), Vector(0,0,1));
    const Sphere s;
    const std::vector<Intersection> xs = Sphere::intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == 4.0);
    REQUIRE(xs[1].getT() == 6.0);
}

TEST_CASE("A ray intersects a sphere at a tangent") {
    const Ray r(Point(0, 1, -5), Vector(0, 0, 1));
    const Sphere s;
    const std::vector<Intersection> xs = Sphere::intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == 5.0);
    REQUIRE(xs[1].getT() == 5.0);
}

TEST_CASE("A ray misses a sphere") {
    const Ray r(Point(0, 2, -5), Vector(0, 0, 1));
    const Sphere s;
    const std::vector<Intersection> xs = Sphere::intersect(s, r);

    REQUIRE(xs.size() == 0);
}

TEST_CASE("A ray originates inside a sphere") {
    const Ray r(Point(0, 0, 0), Vector(0, 0, 1));
    const Sphere s;
    const std::vector<Intersection> xs = Sphere::intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == -1.0);
    REQUIRE(xs[1].getT() == 1.0);
}

TEST_CASE("A sphere is behind a ray") {
    const Ray r(Point(0, 0, 5), Vector(0, 0, 1));
    const Sphere s;
    const std::vector<Intersection> xs = Sphere::intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == -6.0);
    REQUIRE(xs[1].getT() == -4.0);
}

TEST_CASE("An intersection encapsulates t and object") {
    const Object *s = new Sphere();
    const Intersection i(3.5,*s);

    REQUIRE(i.getT() == 3.5);
    REQUIRE(&i.getObject() == s);
}

TEST_CASE("Aggregating intersections") {
    const Sphere s;
    const Intersection i1(1, s);
    const Intersection i2(2, s);
    const std::vector<Intersection> xs = intersections(i1, i2);

    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == 1);
    REQUIRE(xs[1].getT() == 2);
}

TEST_CASE("The hit, when all intersections have positive t") {
    const Sphere s;
    const Intersection i1(1, s);
    const Intersection i2(2, s);
    const std::vector<Intersection> xs = intersections(i2, i1);
    const Intersection* i = hit(xs);

    REQUIRE(*i == i1);
}

TEST_CASE("The hit, when some intersections have negative t") {
    const Sphere s;
    const Intersection i1(-1, s);
    const Intersection i2(1, s);
    const std::vector<Intersection> xs = intersections(i2, i1);
    const Intersection *i = hit(xs);

    REQUIRE(*i == i2);
}

TEST_CASE("The hit, when all intersections have negative t") {
    const Sphere s;
    const Intersection i1(-2, s);
    const Intersection i2(-1, s);
    const std::vector<Intersection> xs = intersections(i2, i1);
    const Intersection *i = hit(xs);

    REQUIRE(i == nullptr);
}

TEST_CASE("The hit is always the lowest nonnegative intersection") {
    const Sphere s;
    const Intersection i1(5, s);
    const Intersection i2(7, s);
    const Intersection i3(-3,s);
    const Intersection i4(2,s);
    const std::vector<Intersection> xs = intersections(i1,i2,i3,i4);
    const Intersection *i = hit(xs);

    REQUIRE(*i == i4);
}

TEST_CASE("Translating a ray") {
    const Ray r(Point(1, 2, 3), Vector(0, 1, 0));
    const Matrix m = Matrix::translation(3, 4, 5);
    const Ray r2 = Ray::transform(r, m);

    REQUIRE(r2.getOrigin() == Point(4,6,8));
    REQUIRE(r2.getDirection() == Vector(0,1,0));
}

TEST_CASE("Scaling a ray") {
    const Ray r(Point(1, 2, 3), Vector(0, 1, 0));
    const Matrix m = Matrix::scaling(2, 3, 4);
    const Ray r2 = Ray::transform(r, m);

    REQUIRE(r2.getOrigin() == Point(2,6,12));
    REQUIRE(r2.getDirection() == Vector(0,3,0));
}

TEST_CASE("A sphere's default transformation") {
    const Sphere s;

    REQUIRE(s.getTransform() == Matrix::identity());
}

TEST_CASE("Changing a sphere's transformation") {
    Sphere s;
    const Matrix m = Matrix::translation(2, 3, 4);
    s.setTransform(m);

    REQUIRE(s.getTransform() == m);
}

TEST_CASE("Intersecting a scaled sphere with a ray") {
    const Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    s.setTransform(Matrix::scaling(2, 2, 2));
    const std::vector<Intersection> xs = Sphere::intersect(s, r);

    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].getT() == 3);
    REQUIRE(xs[1].getT() == 7);
}

TEST_CASE("Intersecting a translated sphere with a ray") {
    const Ray r(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s;
    s.setTransform(Matrix::translation(5, 0, 0));
    const std::vector<Intersection> xs = Sphere::intersect(s, r);

    REQUIRE(xs.size() == 0);
}
