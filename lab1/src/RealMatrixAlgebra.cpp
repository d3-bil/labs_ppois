#include "RealMatrix.h"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace lab1 {

namespace {

std::size_t find_pivot_row(const RealMatrix& work, std::size_t column) {
    std::size_t pivot_row = column;
    double max_abs = std::fabs(work.at(column, column));
    for (std::size_t row = column + 1; row < work.rows(); ++row) {
        const double candidate = std::fabs(work.at(row, column));
        if (candidate > max_abs) {
            max_abs = candidate;
            pivot_row = row;
        }
    }
    return pivot_row;
}

void swap_matrix_rows(RealMatrix& work, std::size_t first_row, std::size_t second_row) {
    for (std::size_t col = 0; col < work.cols(); ++col) {
        std::swap(work.at(first_row, col), work.at(second_row, col));
    }
}

void eliminate_below_pivot(RealMatrix& work, std::size_t pivot_index) {
    const double pivot_value = work.at(pivot_index, pivot_index);
    for (std::size_t row = pivot_index + 1; row < work.rows(); ++row) {
        const double factor = work.at(row, pivot_index) / pivot_value;
        for (std::size_t col = pivot_index; col < work.cols(); ++col) {
            work.at(row, col) -= factor * work.at(pivot_index, col);
        }
    }
}

}  // namespace

RealMatrix& RealMatrix::operator+=(const RealMatrix& other) {
    ensure_same_dimensions(other);
    const std::size_t total_elements = rows_ * cols_;
    for (std::size_t index = 0; index < total_elements; ++index) {
        data_[index] += other.data_[index];
    }
    return *this;
}

RealMatrix RealMatrix::operator+(const RealMatrix& other) const {
    RealMatrix result(*this);
    result += other;
    return result;
}

RealMatrix& RealMatrix::operator+=(double scalar) {
    const std::size_t total_elements = rows_ * cols_;
    for (std::size_t index = 0; index < total_elements; ++index) {
        data_[index] += scalar;
    }
    return *this;
}

RealMatrix RealMatrix::operator+(double scalar) const {
    RealMatrix result(*this);
    result += scalar;
    return result;
}

RealMatrix& RealMatrix::operator-=(const RealMatrix& other) {
    ensure_same_dimensions(other);
    const std::size_t total_elements = rows_ * cols_;
    for (std::size_t index = 0; index < total_elements; ++index) {
        data_[index] -= other.data_[index];
    }
    return *this;
}

RealMatrix RealMatrix::operator-(const RealMatrix& other) const {
    RealMatrix result(*this);
    result -= other;
    return result;
}

RealMatrix& RealMatrix::operator-=(double scalar) {
    return (*this += (-scalar));
}

RealMatrix RealMatrix::operator-(double scalar) const {
    RealMatrix result(*this);
    result -= scalar;
    return result;
}

RealMatrix RealMatrix::operator*(const RealMatrix& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Incompatible matrix sizes for multiplication.");
    }
    RealMatrix product(rows_, other.cols_, 0.0);
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = 0; col < other.cols_; ++col) {
            double accumulator = 0.0;
            for (std::size_t shared = 0; shared < cols_; ++shared) {
                accumulator += at(row, shared) * other.at(shared, col);
            }
            product.at(row, col) = accumulator;
        }
    }
    return product;
}

RealMatrix& RealMatrix::operator*=(double scalar) {
    const std::size_t total_elements = rows_ * cols_;
    for (std::size_t index = 0; index < total_elements; ++index) {
        data_[index] *= scalar;
    }
    return *this;
}

RealMatrix RealMatrix::operator*(double scalar) const {
    RealMatrix result(*this);
    result *= scalar;
    return result;
}

RealMatrix& RealMatrix::operator/=(double scalar) {
    if (std::fabs(scalar) <= kMatrixEpsilon) {
        throw std::invalid_argument("Division of matrix by zero scalar.");
    }
    return (*this *= (1.0 / scalar));
}

RealMatrix RealMatrix::operator/(double scalar) const {
    RealMatrix result(*this);
    result /= scalar;
    return result;
}

RealMatrix RealMatrix::pow(unsigned int exponent) const {
    if (!is_square()) {
        throw std::invalid_argument("Only square matrices can be raised to a power.");
    }
    RealMatrix result = make_identity(rows_);
    RealMatrix base(*this);
    unsigned int remaining = exponent;
    while (remaining > 0) {
        if ((remaining % 2U) == 1U) {
            result = result * base;
        }
        base = base * base;
        remaining /= 2U;
    }
    return result;
}

RealMatrix RealMatrix::operator^(unsigned int exponent) const {
    return pow(exponent);
}

RealMatrix& RealMatrix::operator^=(unsigned int exponent) {
    *this = pow(exponent);
    return *this;
}

double RealMatrix::determinant() const {
    if (!is_square()) {
        throw std::invalid_argument("Determinant is defined only for non-empty square matrices.");
    }
    RealMatrix work(*this);
    double det_value = 1.0;
    for (std::size_t col = 0; col < work.rows(); ++col) {
        const std::size_t pivot_row = find_pivot_row(work, col);
        if (std::fabs(work.at(pivot_row, col)) <= kMatrixEpsilon) {
            return 0.0;
        }
        if (pivot_row != col) {
            swap_matrix_rows(work, col, pivot_row);
            det_value = -det_value;
        }
        det_value *= work.at(col, col);
        eliminate_below_pivot(work, col);
    }
    return det_value;
}

double RealMatrix::norm() const {
    double sum_squares = 0.0;
    const std::size_t total_elements = rows_ * cols_;
    for (std::size_t index = 0; index < total_elements; ++index) {
        sum_squares += data_[index] * data_[index];
    }
    return std::sqrt(sum_squares);
}

RealMatrix operator+(double scalar, const RealMatrix& matrix) {
    return matrix + scalar;
}

RealMatrix operator*(double scalar, const RealMatrix& matrix) {
    return matrix * scalar;
}

}  // namespace lab1
