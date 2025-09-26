#include "catch.hpp"
#include "Color.h"
#include "Light.h"
#include "Point.h"

TEST_CASE("A point light has a position and intensity") {
    const Color intensity(1, 1, 1);
    const Point position(0, 0, 0);
    const Light light(position, intensity);

    REQUIRE(light.getPosition() == position);
    REQUIRE(light.getIntensity() == intensity);
}
