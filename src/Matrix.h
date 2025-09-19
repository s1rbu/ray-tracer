#ifndef RAY_TRACER_MATRIX_H
#define RAY_TRACER_MATRIX_H
#include <vector>
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
};

#endif //RAY_TRACER_MATRIX_H
