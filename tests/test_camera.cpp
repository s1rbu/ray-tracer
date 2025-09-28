#include "Camera.h"
#include "catch.hpp"

using std::numbers::pi;

TEST_CASE("Constructing a camera") {
    const double hSize = 160;
    const double vSize = 120;
    const double fOV = pi / 2;
    const Camera c(hSize, vSize, fOV);

    REQUIRE(c.getHSize() == 160);
    REQUIRE(c.getVSize() == 120);
    REQUIRE(c.getFOV() == pi / 2);
    REQUIRE(c.getTransform() == Matrix::identity());
}

TEST_CASE("The pixel size for a horizontal canvas") {
    const Camera c(200, 125, pi / 2);
    REQUIRE(c.getPixelSize() == Approx(0.01));
}

TEST_CASE("The pixel size for a vertical canvas") {
    const Camera c(125, 200, pi / 2);
    REQUIRE(c.getPixelSize() == Approx(0.01));
}

TEST_CASE("Constructing a ray through the center of the canvas") {
    const Camera c(201, 101, pi / 2);
    const Ray r = c.rayForPixel(100, 50);

    REQUIRE(r.getOrigin() == Point(0, 0, 0));
    REQUIRE(r.getDirection() == Vector(0, 0, -1));
}

TEST_CASE("Constructing a ray through a corner of the canvas") {
    const Camera c(201, 101, pi / 2);
    const Ray r = c.rayForPixel(0, 0);

    REQUIRE(r.getOrigin() == Point(0, 0, 0));
    REQUIRE(r.getDirection().getX() == Approx(0.66519).epsilon(1e-5));
    REQUIRE(r.getDirection().getY() == Approx(0.33259).epsilon(1e-5));
    REQUIRE(r.getDirection().getZ() == Approx(-0.66851).epsilon(1e-5));
}

TEST_CASE("Constructing a ray when the camera is transformed") {
    Camera c(201, 101, pi / 2);
    c.setTransform(Matrix::rotationY(pi / 4) * Matrix::translation(0, -2, 5));

    const Ray r = c.rayForPixel(100, 50);

    REQUIRE(r.getOrigin().getX() == Approx(0).epsilon(1e-5));
    REQUIRE(r.getOrigin().getY() == Approx(2).epsilon(1e-5));
    REQUIRE(r.getOrigin().getZ() == Approx(-5).epsilon(1e-5));

    REQUIRE(r.getDirection().getX() == Approx(std::sqrt(2)/2).epsilon(1e-5));
    REQUIRE(r.getDirection().getY() == Approx(0).epsilon(1e-5));
    REQUIRE(r.getDirection().getZ() == Approx(-std::sqrt(2)/2).epsilon(1e-5));
}
