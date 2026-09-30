#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

class Matrix {
public:
    Matrix(size_t rows = 0, size_t cols = 0) : rows_(rows), cols_(cols), 
       data_(static_cast<float*>(std::malloc(rows * cols * sizeof(float)))), is_freeable_(true)
    {
        std::cout << "matrix was made\n";
    };

    Matrix(float* data, size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(data), is_freeable_(false) {
            std::cout << "matrix was made\n";
        };

    ~Matrix() {
        if (is_freeable_) {
            std::free(data_);
        }
    }

    float operator[](size_t id_row, size_t id_col) const {
        return *(data_ + id_row * cols_ + id_col);
    }

    float& operator[](size_t id_row, size_t id_col) {
        return *(data_ + id_row * cols_ + id_col);
    }

    Matrix operator+(const Matrix& other) {
        assert(other.cols_ == cols_ && other.rows_ == rows_);

        Matrix result(rows_, cols_);
        for (size_t row = 0; row < rows_; row++) {
            for (size_t col = 0; col < cols_; col++) {
                result[row, col] = (*this)[row, col] + other[row, col];
            }
        }

        return result;
    }

    Matrix operator-(const Matrix& other) {
        assert(other.cols_ == cols_ && other.rows_ == rows_);

        Matrix result(rows_, cols_);
        for (size_t row = 0; row < rows_; row++) {
            for (size_t col = 0; col < cols_; col++) {
                result[row, col] = (*this)[row, col] - other[row, col];
            }
        }

        return result;
    }

    Matrix operator*(const Matrix& other) {
        assert(other.rows_ == cols_);

        Matrix result(rows_, other.cols_);
        for (size_t row = 0; row < rows_; row++) {
            for (size_t col = 0; col < cols_; col++) {
                float accum = 0;
                for (size_t accum_ind = 0; accum_ind < other.rows_; accum_ind++) {
                    accum += (*this)[row, accum_ind] * other[accum_ind, col];
                }
                result[row, col] = accum;
            }
        }

        return result;
    }

    void fill() {
        int counter = 0;
        for (size_t row = 0; row < rows_; row++) {
            for (size_t col = 0; col < cols_; col++) {
                (*this)[row, col] = counter;
                counter++;
            }
        }
    }

    size_t cols() const {
        return cols_;
    }

    size_t rows() const {
        return rows_;
    }

    Matrix operator*(float multiplyer) {
        Matrix result(rows_, cols_);
        for (size_t row = 0; row < rows_; row++) {
            for (size_t col = 0; col < cols_; col++) {
                result[row, col] = (*this)[row, col] * multiplyer;
            }
        }

        return result;
    }

    Matrix operator&(const Matrix& other) {
        assert(other.cols_ == cols_ && other.rows_ == rows_);

        Matrix result(rows_, cols_);
        for (size_t row = 0; row < rows_; row++) {
            for (size_t col = 0; col < cols_; col++) {
                result[row, col] = (*this)[row, col] * other[row, col];
            }
        }

        return result;
    }

private:
    size_t rows_;
    size_t cols_;
    float* data_;
    bool is_freeable_;
};

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    out << "Matrix:\n";
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            out << matrix[i, j] << " ";
        }
        out << std::endl;
    }

    return out;
}

int main() {
    Matrix A(3,4);
    Matrix B(4, 3);

    A.fill();
    B.fill();

    Matrix C = A * B;
    std::cout << C;
}