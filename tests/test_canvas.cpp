#include "Canvas.h"
#include "catch.hpp"
#include "Color.h"

TEST_CASE("Colors are tuples") {
    const Color c(-0.5, -0.4, 1.7);

    REQUIRE(c.red() == -0.5);
    REQUIRE(c.green() == -0.4);
    REQUIRE(c.blue() == 1.7);
}

TEST_CASE("Adding colors") {
    const Color c1(0.9, 0.6, 0.75);
    const Color c2(0.7, 0.1, 0.25);

    REQUIRE(c1 + c2 == Color(1.6, 0.7, 1.0));
}

TEST_CASE("Subtracting colors") {
    const Color c1(0.9, 0.6, 0.75);
    const Color c2(0.7, 0.1, 0.25);

    REQUIRE(c1 - c2 == Color(0.2, 0.5, 0.5));
}

TEST_CASE("Multiplying a color by a scalar") {
    const Color c(0.2, 0.3, 0.4);

    REQUIRE(c * 2 == Color(0.4, 0.6, 0.8));
}

TEST_CASE("Multiplying colors") {
    const Color c1(1, 0.2, 0.4);
    const Color c2(0.9, 1, 0.1);

    // REQUIRE(c1*c2 == Color(0.9, 0.2, 0.04));
    REQUIRE(Color::hadamard(c1, c2) == Color(0.9, 0.2, 0.04));
}

TEST_CASE("Creating a canvas") {
    const Canvas c(10, 20);

    REQUIRE(c.getWidth() == 10);
    REQUIRE(c.getHeight() == 20);
    for (int y = 0; y < c.getHeight(); y++) {
        for (int x = 0; x < c.getWidth(); x++) {
            REQUIRE(c.pixelAt(x, y) == Color(0, 0,0 ));
        }
    }
}

TEST_CASE("Writing pixels to a canvas") {
    Canvas c(10, 20);
    const Color red(1.0, 0.0, 0.0);
    const Color black(0.0, 0.0, 0.0);

    REQUIRE(c.pixelAt(2, 3) == black);

    c.writePixel(2, 3, red);
    REQUIRE(c.pixelAt(2, 3) == red);
}
