#ifndef RAY_TRACER_MATRIX_H
#define RAY_TRACER_MATRIX_H
#include <vector>
#include <cmath>

#include "Point.h"
#include "Tuple.h"

class Matrix {
    std::vector<std::vector<double>> data;

public:
    Matrix() = default;

    Matrix(const int rows, const int cols) : data(rows, std::vector<double>(cols, 0.0)) {
    }

    Matrix(const std::initializer_list<std::initializer_list<double> > values)
        : data{} {
        for (auto row: values) {
            data.emplace_back(row.begin(), row.end());
        }
    }

    double operator()(const int row, const int col) const {
        return data[row][col];
    }

    bool operator==(const Matrix &other) const {
        if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) return false;

        const int rows = data.size();
        const int cols = data[0].size();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (std::fabs(data[i][j] - other.data[i][j]) > EPSILON) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix operator*(const Matrix & other) const {
        Matrix M;

        const int N = this->data.size();
        M.data.assign(N, std::vector<double>(N, 0.0));

        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) {
                for (int k=0;k<N;k++) {
                    M.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return M;
    }

    Tuple operator*(const Tuple &other) const {
        const int N = this->data.size();
        const std::vector<double> tuple = {other.getX(), other.getY(), other.getZ(), other.getW()};
        std::vector<double> aux(4, 0.0);

        for (int i=0;i<N;i++) {
            for (int j=0;j<N;j++) {
                aux[i] += this->data[i][j] * tuple[j];
            }
        }

        return {aux[0], aux[1], aux[2], aux[3]};
    }

    static Matrix identity(const int size = 4) {
        Matrix M(size, size);
        for (int i = 0; i < size; i++) {
            M.data[i][i] = 1.0;
        }

        return M;
    }

    static Matrix transpose(const Matrix &other) {
        const int N = other.data.size();
        Matrix M(N, N);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                M.data[j][i] = other.data[i][j];
            }
        }

        return M;
    }

    static double determinant(const Matrix &m) {
        double det = 0.0;

        if (m.data.size() == 2)
            return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];

        for (int i = 0; i < m.data.size(); i++) {
            det += m.data[0][i] * cofactor(m, 0, i);
        }

        return det;
    }

    static Matrix submatrix(const Matrix &other, const int row, const int col) {
        const int N = other.data.size();
        Matrix M(N - 1, N - 1);

        int R = 0;
        for (int i = 0; i < N; i++) {
            if (i == row)
                continue;
            int C = 0;
            for (int j = 0; j < N; j++) {
                if (j == col)
                    continue;
                M.data[R][C] = other.data[i][j];
                C++;
            }
            R++;
        }

        return M;
    }

    static double minor(const Matrix &other, const int row, const int col) {
        const Matrix M = submatrix(other, row, col);
        return determinant(M);
    }

    static double cofactor(const Matrix &other, const int row, const int col) {
        const double minor = Matrix::minor(other, row, col);

        if ((row + col) % 2 == 1)
            return -minor;

        return minor;
    }

    bool isInvertible() const {
        if (determinant(*this) == 0.0) {
            return false;
        }

        return true;
    }

    static Matrix inverse(const Matrix &other) {
        if (!other.isInvertible()) {
            throw std::runtime_error("Matrix is not invertible");
        }

        const double det = determinant(other);
        const int N = other.data.size();
        Matrix M(N, N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                const double c = cofactor(other, i, j);
                M.data[j][i] = c / det;
            }
        }

        return M;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        const int N = matrix.data.size();
        for (int i = 0; i < N; i++) {
            os << "| ";
            for (int j = 0; j < N; j++) {
                os << matrix.data[i][j];
                if (j != N - 1) {
                    os << ", ";
                }
            }
            os << " |\n";
        }

        return os;
    }

    static Matrix translation(const double x, const double y, const double z) {
        Matrix M = identity();
        M.data[0][3] = x;
        M.data[1][3] = y;
        M.data[2][3] = z;

        return M;
    }

    static Matrix scaling(const double x, const double y, const double z) {
        Matrix M = identity();
        M.data[0][0] = x;
        M.data[1][1] = y;
        M.data[2][2] = z;

        return M;
    }

    static Matrix rotationX(const double r) {
        Matrix M = identity();
        M.data[1][1] = cos(r);
        M.data[1][2] = -sin(r);
        M.data[2][1] = sin(r);
        M.data[2][2] = cos(r);

        return M;
    }

    static Matrix rotationY(const double r) {
        Matrix M = identity();
        M.data[0][0] = cos(r);
        M.data[0][2] = sin(r);
        M.data[2][0] = -sin(r);
        M.data[2][2] = cos(r);

        return M;
    }

    static Matrix rotationZ(const double r) {
        Matrix M = identity();
        M.data[0][0] = cos(r);
        M.data[0][1] = -sin(r);
        M.data[1][0] = sin(r);
        M.data[1][1] = cos(r);

        return M;
    }

    static Matrix shearing(const double xY, const double xZ, const double yX, const double yZ, const double zX, const double zY) {
        Matrix M = identity();
        M.data[0][1] = xY;
        M.data[0][2] = xZ;
        M.data[1][0] = yX;
        M.data[1][2] = yZ;
        M.data[2][0] = zX;
        M.data[2][1] = zY;

        return M;
    }

    static Matrix viewTransform(const Point &from, const Point &to, const Vector &up) {
        const Vector forward = Vector::normalize(to - from);
        const Vector upn = Vector::normalize(up);
        const Vector left = Vector::cross(forward, upn);
        const Vector true_up = Vector::cross(left, forward);

        const auto orientation = Matrix({
            { left.getX(),     left.getY(),     left.getZ(),     0 },
            { true_up.getX(),  true_up.getY(),  true_up.getZ(),  0 },
            { -forward.getX(), -forward.getY(), -forward.getZ(), 0 },
            { 0,               0,               0,               1 }
        });

        return orientation * Matrix::translation(-from.getX(), -from.getY(), -from.getZ());
    }
};

#endif //RAY_TRACER_MATRIX_H
