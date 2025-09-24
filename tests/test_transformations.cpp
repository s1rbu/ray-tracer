#include "catch.hpp"
#include "Matrix.h"
#include "Point.h"

using namespace std::numbers;

TEST_CASE("Multiplying by a translation matrix") {
    const Matrix transform = Matrix::translation(5, -3, 2);
    const Point p(-3, 4, 5);

    REQUIRE(transform * p == Point(2,1,7));
}

TEST_CASE("Multiplying by the inverse of a translation matrix") {
    const Matrix transform = Matrix::translation(5, -3, 2);
    const Matrix inverse = Matrix::inverse(transform);
    const Point p(-3, 4, 5);

    REQUIRE(inverse * p == Point(-8,7,3));
}

TEST_CASE("Translation does not affect vectors") {
    const Matrix transform = Matrix::translation(5, -3, 2);
    const Vector v(-3, 4, 5);

    REQUIRE(transform * v == v);
}

TEST_CASE("A scaling matrix applied to a point") {
    const Matrix transform = Matrix::scaling(2, 3, 4);
    const Point p(-4, 6, 8);

    REQUIRE(transform * p == Point(-8,18,32));
}

TEST_CASE("A scaling matrix applied to a vector") {
    const Matrix transform = Matrix::scaling(2, 3, 4);
    const Vector v(-4, 6, 8);

    REQUIRE(transform * v == Vector(-8,18,32));
}

TEST_CASE("Multiplying by the inverse of a scaling matrix") {
    const Matrix transform = Matrix::scaling(2, 3, 4);
    const Matrix inverse = Matrix::inverse(transform);
    const Vector v(-4, 6, 8);

    REQUIRE(inverse * v == Vector(-2,2,2));
}

TEST_CASE("Reflection is scaling by a negative value") {
    const Matrix transform = Matrix::scaling(-1, 1, 1);
    const Point p(2, 3, 4);

    REQUIRE(transform * p == Point(-2,3,4));
}

TEST_CASE("Rotating a point around the x axis") {
    const Point p(0, 1, 0);
    const Matrix halfQuarter = Matrix::rotationX(pi / 4);
    const Matrix fullQuarter = Matrix::rotationX(pi / 2);

    REQUIRE(halfQuarter * p == Point(0, sqrt(2)/2, sqrt(2)/2));
    REQUIRE(fullQuarter * p == Point(0,0,1));
}

TEST_CASE("The inverse of an x-rotation rotates in the opposite direction") {
    const Point p(0, 1, 0);
    const Matrix halfQuarter = Matrix::rotationX(pi / 4);
    const Matrix inv = Matrix::inverse(halfQuarter);

    REQUIRE(inv * p == Point(0, sqrt(2)/2, -sqrt(2)/2));
}

TEST_CASE("Rotating a point around the y axis") {
    const Point p(0, 0, 1);
    const Matrix halfQuarter = Matrix::rotationY(pi / 4);
    const Matrix fullQuarter = Matrix::rotationY(pi / 2);

    REQUIRE(halfQuarter * p == Point(sqrt(2)/2, 0, sqrt(2)/2));
    REQUIRE(fullQuarter * p == Point(1,0,0));
}

TEST_CASE("Rotating a point around the z axis") {
    const Point p(0, 1, 0);
    const Matrix halfQuarter = Matrix::rotationZ(pi / 4);
    const Matrix fullQuarter = Matrix::rotationZ(pi / 2);

    REQUIRE(halfQuarter * p == Point(-sqrt(2)/2, sqrt(2)/2, 0));
    REQUIRE(fullQuarter * p == Point(-1,0, 0));
}

TEST_CASE("A shearing transformation moves x in proportion to y") {
    const Matrix transform = Matrix::shearing(1,0,0,0,0,0);
    const Point p(2,3,4);

    REQUIRE(transform * p == Point(5,3,4));
}

TEST_CASE("A shearing transformation moves x in proportion to z") {
    const Matrix transform = Matrix::shearing(0, 1, 0, 0, 0, 0);
    const Point p(2, 3, 4);

    REQUIRE(transform * p == Point(6, 3, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to x") {
    const Matrix transform = Matrix::shearing(0, 0, 1, 0, 0, 0);
    const Point p(2, 3, 4);

    REQUIRE(transform * p == Point(2, 5, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to z") {
    const Matrix transform = Matrix::shearing(0, 0, 0, 1, 0, 0);
    const Point p(2, 3, 4);

    REQUIRE(transform * p == Point(2, 7, 4));
}

TEST_CASE("A shearing transformation moves z in proportion to x") {
    const Matrix transform = Matrix::shearing(0, 0, 0, 0, 1, 0);
    const Point p(2, 3, 4);

    REQUIRE(transform * p == Point(2, 3, 6));
}

TEST_CASE("A shearing transformation moves z in proportion to y") {
    const Matrix transform = Matrix::shearing(0, 0, 0, 0, 0, 1);
    const Point p(2, 3, 4);

    REQUIRE(transform * p == Point(2, 3, 7));
}

TEST_CASE("Individual transformations are applied in sequence") {
    const Point p(1, 0, 1);
    const Matrix A = Matrix::rotationX(pi / 2);
    const Matrix B = Matrix::scaling(5, 5, 5);
    const Matrix C = Matrix::translation(10, 5, 7);
    const auto p2 = Point(A * p);

    REQUIRE(p2 == Point(1, -1, 0));

    const auto p3 = Point(B * p2);
    REQUIRE(p3 == Point(5, -5, 0));

    const auto p4 = Point(C * p3);
    REQUIRE(p4 == Point(15, 0, 7));
}

TEST_CASE("Chained transformations must be applied in reverse order") {
    const Point p(1, 0, 1);
    const Matrix A = Matrix::rotationX(pi / 2);
    const Matrix B = Matrix::scaling(5, 5, 5);
    const Matrix C = Matrix::translation(10, 5, 7);
    const Matrix T = C * B * A;

    REQUIRE(T * p == Point(15, 0, 7));
}
