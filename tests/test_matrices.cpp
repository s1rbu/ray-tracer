#include "catch.hpp"
#include "Matrix.h"

TEST_CASE("Constructing and inspecting a 4x4 matrix") {
    const Matrix M({
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}
    });

    REQUIRE(M(0,0) == 1);
    REQUIRE(M(0,3)==4);
    REQUIRE(M(1,0) == 5.5);
    REQUIRE(M(1,2) == 7.5);
    REQUIRE(M(2,2) == 11);
    REQUIRE(M(3,0) == 13.5);
    REQUIRE(M(3,2) == 15.5);
}

TEST_CASE("A 2x2 matrix ought to be representable") {
    const Matrix M({
        {-3, 5},
        {1, -2}
    });

    REQUIRE(M(0,0) == -3);
    REQUIRE(M(0,1) == 5);
    REQUIRE(M(1,0) == 1);
    REQUIRE(M(1,1) == -2);
}

TEST_CASE("A 3x3 matrix ought to be representable") {
    const Matrix M({
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1}
    });

    REQUIRE(M(0,0) == -3);
    REQUIRE(M(1,1) == -2);
    REQUIRE(M(2,2) == 1);
}

TEST_CASE("Matrix equality with identical matrices") {
    const Matrix A({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });

    const Matrix B({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });
    REQUIRE(A == B);
}

TEST_CASE("Matrix equality with different matrices") {
    const Matrix A({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });

    const Matrix B({
        {2, 3, 4, 5},
        {6, 7, 8, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    });

    REQUIRE(A != B);
}

TEST_CASE("Multiplying two matrices") {
    const Matrix A({
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    });

    const Matrix B({
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8}
    });

    const Matrix M({
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}
    });

    REQUIRE(A * B == M);
}

TEST_CASE("A matrix multiplied by a tuple") {
    const Matrix A({
        {1,2,3,4},
        {2,4,4,2},
        {8,6,4,1},
        {0,0,0,1}
    });

    const Tuple b(1,2,3,1);

    REQUIRE(A*b == Tuple(18,24,33,1));
}