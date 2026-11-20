#include "RealMatrix.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <stdexcept>

namespace lab1 {

namespace {

bool is_zero_value(double value) {
    return std::fabs(value) <= kMatrixEpsilon;
}

}  // namespace

void RealMatrix::resize(std::size_t new_rows, std::size_t new_cols, double fill_value) {
    RealMatrix resized(new_rows, new_cols, fill_value);
    const std::size_t copy_rows = std::min(rows_, new_rows);
    const std::size_t copy_cols = std::min(cols_, new_cols);
    for (std::size_t row = 0; row < copy_rows; ++row) {
        for (std::size_t col = 0; col < copy_cols; ++col) {
            resized.at(row, col) = at(row, col);
        }
    }
    *this = resized;
}

void RealMatrix::load_from_file(const std::string& file_path) {
    std::ifstream file_stream(file_path);
    if (!file_stream.is_open()) {
        throw std::runtime_error("Unable to open matrix file: " + file_path);
    }
    RealMatrix loaded;
    if (!(file_stream >> loaded)) {
        throw std::runtime_error("Invalid matrix format in file: " + file_path);
    }
    *this = loaded;
}

RealMatrix RealMatrix::extract_submatrix(std::size_t start_row,
                                         std::size_t start_col,
                                         std::size_t sub_rows,
                                         std::size_t sub_cols) const {
    if (start_row + sub_rows > rows_ || start_col + sub_cols > cols_) {
        throw std::out_of_range("Requested submatrix exceeds matrix bounds.");
    }
    RealMatrix submatrix(sub_rows, sub_cols, 0.0);
    for (std::size_t row = 0; row < sub_rows; ++row) {
        for (std::size_t col = 0; col < sub_cols; ++col) {
            submatrix.at(row, col) = at(start_row + row, start_col + col);
        }
    }
    return submatrix;
}

bool RealMatrix::is_square() const {
    return rows_ > 0 && rows_ == cols_;
}

bool RealMatrix::is_zero() const {
    const std::size_t total_elements = rows_ * cols_;
    for (std::size_t index = 0; index < total_elements; ++index) {
        if (!is_zero_value(data_[index])) {
            return false;
        }
    }
    return total_elements > 0;
}

bool RealMatrix::is_diagonal() const {
    if (!is_square()) {
        return false;
    }
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = 0; col < cols_; ++col) {
            if (row != col && !is_zero_value(at(row, col))) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::is_identity() const {
    if (!is_diagonal()) {
        return false;
    }
    for (std::size_t index = 0; index < rows_; ++index) {
        if (std::fabs(at(index, index) - 1.0) > kMatrixEpsilon) {
            return false;
        }
    }
    return true;
}

bool RealMatrix::is_symmetric() const {
    if (!is_square()) {
        return false;
    }
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = row + 1; col < cols_; ++col) {
            if (std::fabs(at(row, col) - at(col, row)) > kMatrixEpsilon) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::is_upper_triangular() const {
    if (!is_square()) {
        return false;
    }
    for (std::size_t row = 1; row < rows_; ++row) {
        for (std::size_t col = 0; col < row; ++col) {
            if (!is_zero_value(at(row, col))) {
                return false;
            }
        }
    }
    return true;
}

bool RealMatrix::is_lower_triangular() const {
    if (!is_square()) {
        return false;
    }
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = row + 1; col < cols_; ++col) {
            if (!is_zero_value(at(row, col))) {
                return false;
            }
        }
    }
    return true;
}

RealMatrix RealMatrix::transpose() const {
    RealMatrix transposed(cols_, rows_, 0.0);
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = 0; col < cols_; ++col) {
            transposed.at(col, row) = at(row, col);
        }
    }
    return transposed;
}

}  // namespace lab1
