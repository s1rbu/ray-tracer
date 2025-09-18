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
