#include "Canvas.h"
#include "CanvasUtils.h"
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

TEST_CASE("Constructing the PPM header") {
    const Canvas c(5, 3);
    const std::string ppm = canvas2ppm(c);

    std::istringstream stream(ppm);
    std::vector<std::string> lines(3);
    std::getline(stream, lines[0]);
    std::getline(stream, lines[1]);
    std::getline(stream, lines[2]);

    REQUIRE(lines[0] == "P3");
    REQUIRE(lines[1] == "5 3");
    REQUIRE(lines[2] == "255");
}

TEST_CASE("Constructing the PPM pixel data") {
    Canvas c(5, 3);
    const Color c1(1.5, 0, 0);
    const Color c2(0, 0.5, 0);
    const Color c3(-0.5, 0, 1);

    c.writePixel(0, 0, c1);
    c.writePixel(2, 1, c2);
    c.writePixel(4, 2, c3);

    std::string ppm = canvas2ppm(c), aux;
    std::istringstream stream(ppm);
    std::vector<std::string> lines;
    for (int i = 0; i < 3; i++) {
        std::getline(stream, aux);
    }
    while (std::getline(stream, aux)) {
        lines.push_back(aux);
    }
    REQUIRE(Catch::trim(lines[0]) == "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    REQUIRE(Catch::trim(lines[1]) == "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
    REQUIRE(Catch::trim(lines[2]) == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
    REQUIRE(lines.size() == 3);
}
