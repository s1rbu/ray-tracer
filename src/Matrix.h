#ifndef RAY_TRACER_MATRIX_H
#define RAY_TRACER_MATRIX_H
#include <vector>

static constexpr double EPSILON = 1e-5;

class Matrix {
    std::vector<std::vector<double> > data;

public:
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
};

#endif //RAY_TRACER_MATRIX_H
