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

TEST_CASE("Multiplying a matrix by the identity matrix") {
    const Matrix A({
        {0, 1, 2, 4},
        {1, 2, 4, 8},
        {2, 4, 8, 16},
        {4, 8, 16, 32}
    });

    REQUIRE(A * Matrix::identity(4) == A);
}

TEST_CASE("Multiplying the identity matrix by a tuple") {
    const Tuple a(1, 2, 3, 4);

    REQUIRE(Matrix::identity() * a == a);
}

TEST_CASE("Transposing a matrix") {
    const Matrix A({
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
        {0, 0, 5, 8}
    });
    const Matrix ATransposed({
        {0, 9, 1, 0},
        {9, 8, 8, 0},
        {3, 0, 5, 5},
        {0, 8, 3, 8}
    });

    REQUIRE(Matrix::transpose(A) == ATransposed);
}

TEST_CASE("Transposing the identity matrix") {
    const Matrix A = Matrix::transpose(Matrix::identity());

    REQUIRE(A == Matrix::identity());
}

TEST_CASE("Calculating the determinant of a 2x2 matrix") {
    const Matrix A({
        {1, 5},
        {-3, 2}
    });

    REQUIRE(Matrix::determinant(A) == 17);
}

TEST_CASE("A submatrix of a 3x3 matrix is a 2x2 matrix") {
    const Matrix A({
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3}
    });

    const Matrix ASubmatrix({
        {-3, 2},
        {0, 6}
    });

    REQUIRE(Matrix::submatrix(A,0,2) == ASubmatrix);
}

TEST_CASE("A submatrix of a 4x4 matrix is a 3x3 matrix") {
    const Matrix A({
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
    });
    const Matrix ASubmatrix({
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}
    });

    REQUIRE(Matrix::submatrix(A,2,1) == ASubmatrix);
}

TEST_CASE("Calculating a minor of a 3x3 matrix") {
    const Matrix A({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    });

    const Matrix B = Matrix::submatrix(A, 1, 0);

    REQUIRE(Matrix::determinant(B) == 25);
    REQUIRE(Matrix::minor(A,1,0) == 25);
}

TEST_CASE("Calculating a cofactor of a 3x3 matrix") {
    const Matrix A({
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    });

    REQUIRE(Matrix::minor(A, 0, 0) == -12);
    REQUIRE(Matrix::cofactor(A, 0, 0) == -12);
    REQUIRE(Matrix::minor(A,1,0) == 25);
    REQUIRE(Matrix::cofactor(A,1,0)==-25);
}

TEST_CASE("Calculating the determinant of a 3x3 matrix") {
    const Matrix A({
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4}
    });

    REQUIRE(Matrix::cofactor(A,0,0) == 56);
    REQUIRE(Matrix::cofactor(A,0,1) == 12);
    REQUIRE(Matrix::cofactor(A,0,2) == -46);
    REQUIRE(Matrix::determinant(A) == -196);
}

TEST_CASE("Calculating the determinant of a 4x4 matrix") {
    const Matrix A({
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    });

    REQUIRE(Matrix::cofactor(A,0,0) == 690);
    REQUIRE(Matrix::cofactor(A,0,1) == 447);
    REQUIRE(Matrix::cofactor(A,0,2) == 210);
    REQUIRE(Matrix::cofactor(A,0,3) == 51);
    REQUIRE(Matrix::determinant(A) == -4071);
}

TEST_CASE("Testing an invertible matrix for invertibility") {
    const Matrix A({
        {6, 4, 4, 4},
        {5, 5, 7, 6},
        {4, -9, 3, -7},
        {9, 1, 7, -6}
    });

    REQUIRE(Matrix::determinant(A) == -2120);
    REQUIRE(A.isInvertible());
}

TEST_CASE("Testing a noninvertible matrix for invertibility") {
    const Matrix A({
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0}
    });

    REQUIRE(Matrix::determinant(A) == 0);
    REQUIRE(!A.isInvertible());
}

TEST_CASE("Calculating the inverse of a matrix") {
    const Matrix A({
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4}
    });

    const Matrix B = Matrix::inverse(A);
    const Matrix BInverse({
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80827, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.81391, -0.30075, 0.30639}
    });

    REQUIRE(Matrix::determinant(A) == 532);
    REQUIRE(Matrix::cofactor(A,2,3) == -160);
    REQUIRE(B(3,2) == -160.0/532.0);
    REQUIRE(Matrix::cofactor(A,3,2) == 105);
    REQUIRE(B(2,3) == 105.0/532.0);
    REQUIRE(B == BInverse);
}

TEST_CASE("Calculating the inverse of another matrix") {
    const Matrix A({
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4}
    });

    const Matrix AInverse({
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692, 0.12308, 0.02564, 0.03077},
        {0.35897, 0.35897, 0.43590, 0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308}
    });

    REQUIRE(Matrix::inverse(A) == AInverse);
}

TEST_CASE("Calculating the inverse of a third matrix") {
    const Matrix A({
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2}
    });

    const Matrix AInverse({
        {-0.04074, -0.07778, 0.14444, -0.22222},
        {-0.07778, 0.03333, 0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926, 0.12963},
        {0.17778, 0.06667, -0.26667, 0.33333}
    });

    REQUIRE(Matrix::inverse(A) == AInverse);
}

TEST_CASE("Multiplying a product by its inverse") {
    const Matrix A({
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1}
    });

    const Matrix B({
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5}
    });

    const Matrix C = A * B;

    REQUIRE(C*Matrix::inverse(B) == A);
}
