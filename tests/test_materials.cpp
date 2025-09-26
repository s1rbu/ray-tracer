#include "catch.hpp"
#include "Material.h"

TEST_CASE("The default material") {
    const Material m;

    REQUIRE(m.getSurfaceColor() == Color(1,1,1));
    REQUIRE(m.getAmbient() == 0.1);
    REQUIRE(m.getDiffuse() == 0.9);
    REQUIRE(m.getSpecular() == 0.9);
    REQUIRE(m.getShininess() == 200.0);
}

TEST_CASE("Moving the eye and light source around") {
    Material m;
    Point position(0, 0, 0);

    SECTION("Lighting with the eye between the light and the surface") {
        const Vector eyeV(0, 0, -1);
        const Vector normalV(0, 0, -1);
        const Light light(Point(0, 0, -10), Color(1, 1, 1));

        const Color result = Material::lighting(m, light, position, eyeV, normalV);
        REQUIRE(result == Color(1.9,1.9,1.9));
    }

    SECTION("Lighting with the eye between light and surface, eye offset 45°") {
        const Vector eyeV(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
        const Vector normalV(0, 0, -1);
        const Light light(Point(0, 0, -10), Color(1, 1, 1));

        const Color result = Material::lighting(m, light, position, eyeV, normalV);
        REQUIRE(result == Color(1.0,1.0,1.0));
    }

    SECTION("Lighting with eye opposite surface, light offset 45°") {
        const Vector eyeV(0, 0, -1);
        const Vector normalV(0, 0, -1);
        const Light light(Point(0, 10, -10), Color(1, 1, 1));

        const Color result = Material::lighting(m, light, position, eyeV, normalV);
        REQUIRE(result == Color(0.7364,0.7364,0.7364));
    }

    SECTION("Lighting with eye in the path of the reflection vector") {
        const Vector eyeV(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
        const Vector normalV(0, 0, -1);
        const Light light(Point(0, 10, -10), Color(1, 1, 1));

        const Color result = Material::lighting(m, light, position, eyeV, normalV);
        REQUIRE(result == Color(1.6364,1.6364,1.6364));
    }

    SECTION("Lighting with the light behind the surface") {
        const Vector eyeV(0, 0, -1);
        const Vector normalV(0, 0, -1);
        const Light light(Point(0, 0, 10), Color(1, 1, 1));

        const Color result = Material::lighting(m, light, position, eyeV, normalV);
        REQUIRE(result == Color(0.1,0.1,0.1));
    }
}
