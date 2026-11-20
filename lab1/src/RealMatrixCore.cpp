#include "RealMatrix.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace lab1 {

RealMatrix::RealMatrix(std::size_t rows, std::size_t cols, double initial_value)
    : rows_(rows), cols_(cols), data_(nullptr) {
    const std::size_t total_elements = rows_ * cols_;
    if (total_elements > 0) {
        data_ = new double[total_elements];
        std::fill(data_, data_ + total_elements, initial_value);
    }
}

RealMatrix::RealMatrix(const RealMatrix& other)
    : rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
    const std::size_t total_elements = rows_ * cols_;
    if (total_elements > 0) {
        data_ = new double[total_elements];
        std::copy(other.data_, other.data_ + total_elements, data_);
    }
}

RealMatrix& RealMatrix::operator=(const RealMatrix& other) {
    if (this == &other) {
        return *this;
    }
    RealMatrix copy(other);
    std::swap(rows_, copy.rows_);
    std::swap(cols_, copy.cols_);
    std::swap(data_, copy.data_);
    return *this;
}

RealMatrix::~RealMatrix() {
    delete[] data_;
}

std::size_t RealMatrix::rows() const {
    return rows_;
}

std::size_t RealMatrix::cols() const {
    return cols_;
}

std::size_t RealMatrix::flat_index(std::size_t row, std::size_t col) const {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Matrix indices are out of bounds.");
    }
    return row * cols_ + col;
}

double& RealMatrix::at(std::size_t row, std::size_t col) {
    return data_[flat_index(row, col)];
}

double RealMatrix::at(std::size_t row, std::size_t col) const {
    return data_[flat_index(row, col)];
}

RealMatrix& RealMatrix::operator++() {
    const std::size_t total_elements = rows_ * cols_;
    for (std::size_t index = 0; index < total_elements; ++index) {
        data_[index] += kElementStep;
    }
    return *this;
}

RealMatrix RealMatrix::operator++(int) {
    RealMatrix previous(*this);
    ++(*this);
    return previous;
}

RealMatrix& RealMatrix::operator--() {
    const std::size_t total_elements = rows_ * cols_;
    for (std::size_t index = 0; index < total_elements; ++index) {
        data_[index] -= kElementStep;
    }
    return *this;
}

RealMatrix RealMatrix::operator--(int) {
    RealMatrix previous(*this);
    --(*this);
    return previous;
}

void RealMatrix::ensure_same_dimensions(const RealMatrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions must match.");
    }
}

RealMatrix RealMatrix::make_identity(std::size_t size) {
    RealMatrix identity(size, size, 0.0);
    for (std::size_t index = 0; index < size; ++index) {
        identity.at(index, index) = 1.0;
    }
    return identity;
}

bool RealMatrix::operator==(const RealMatrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }
    const std::size_t total_elements = rows_ * cols_;
    for (std::size_t index = 0; index < total_elements; ++index) {
        if (std::fabs(data_[index] - other.data_[index]) > kMatrixEpsilon) {
            return false;
        }
    }
    return true;
}

bool RealMatrix::operator!=(const RealMatrix& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& output, const RealMatrix& matrix) {
    output << matrix.rows_ << " " << matrix.cols_ << "\n";
    for (std::size_t row = 0; row < matrix.rows_; ++row) {
        for (std::size_t col = 0; col < matrix.cols_; ++col) {
            if (col > 0) {
                output << " ";
            }
            output << matrix.at(row, col);
        }
        output << "\n";
    }
    return output;
}

std::istream& operator>>(std::istream& input, RealMatrix& matrix) {
    std::size_t new_rows = 0;
    std::size_t new_cols = 0;
    if (!(input >> new_rows >> new_cols)) {
        return input;
    }
    RealMatrix parsed(new_rows, new_cols, 0.0);
    for (std::size_t row = 0; row < new_rows; ++row) {
        for (std::size_t col = 0; col < new_cols; ++col) {
            if (!(input >> parsed.at(row, col))) {
                return input;
            }
        }
    }
    matrix = parsed;
    return input;
}

}  // namespace lab1
