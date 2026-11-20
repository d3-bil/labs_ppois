#ifndef LAB1_REAL_MATRIX_H
#define LAB1_REAL_MATRIX_H

#include <cstddef>
#include <iostream>
#include <string>

namespace lab1 {

/// @brief Точность сравнения элементов вещественной матрицы.
constexpr double kMatrixEpsilon = 1e-9;

/// @brief Шаг изменения каждого элемента при инкременте и декременте.
constexpr double kElementStep = 1.0;

/// @brief Вещественная матрица произвольного размера с ручным управлением памятью.
class RealMatrix {
public:
    /// @brief Создаёт пустую матрицу размером 0x0.
    RealMatrix() = default;

    /// @brief Создаёт матрицу заданного размера, заполненную начальным значением.
    RealMatrix(std::size_t rows, std::size_t cols, double initial_value = 0.0);

    /// @brief Конструктор копирования (глубокое копирование буфера).
    RealMatrix(const RealMatrix& other);

    /// @brief Оператор присваивания копированием.
    RealMatrix& operator=(const RealMatrix& other);

    /// @brief Деструктор, освобождающий динамическую память.
    ~RealMatrix();

    std::size_t rows() const;
    std::size_t cols() const;

    /// @brief Доступ к элементу по индексам с проверкой границ.
    double& at(std::size_t row, std::size_t col);
    double at(std::size_t row, std::size_t col) const;

    RealMatrix& operator++();
    RealMatrix operator++(int);
    RealMatrix& operator--();
    RealMatrix operator--(int);

    // --- Подвариант 1.7.1: структура, файл и свойства ---

    void resize(std::size_t new_rows, std::size_t new_cols, double fill_value = 0.0);
    void load_from_file(const std::string& file_path);
    RealMatrix extract_submatrix(std::size_t start_row,
                                 std::size_t start_col,
                                 std::size_t sub_rows,
                                 std::size_t sub_cols) const;

    bool is_square() const;
    bool is_zero() const;
    bool is_diagonal() const;
    bool is_identity() const;
    bool is_symmetric() const;
    bool is_upper_triangular() const;
    bool is_lower_triangular() const;
    RealMatrix transpose() const;

    // --- Подвариант 1.7.2: алгебраические операции ---

    RealMatrix& operator+=(const RealMatrix& other);
    RealMatrix operator+(const RealMatrix& other) const;

    RealMatrix& operator+=(double scalar);
    RealMatrix operator+(double scalar) const;

    RealMatrix& operator-=(const RealMatrix& other);
    RealMatrix operator-(const RealMatrix& other) const;

    RealMatrix& operator-=(double scalar);
    RealMatrix operator-(double scalar) const;

    RealMatrix operator*(const RealMatrix& other) const;

    RealMatrix& operator*=(double scalar);
    RealMatrix operator*(double scalar) const;

    RealMatrix& operator/=(double scalar);
    RealMatrix operator/(double scalar) const;

    RealMatrix pow(unsigned int exponent) const;
    RealMatrix operator^(unsigned int exponent) const;
    RealMatrix& operator^=(unsigned int exponent);

    double determinant() const;
    double norm() const;

    // --- Сравнение и потоки ---

    bool operator==(const RealMatrix& other) const;
    bool operator!=(const RealMatrix& other) const;

    friend std::ostream& operator<<(std::ostream& output, const RealMatrix& matrix);
    friend std::istream& operator>>(std::istream& input, RealMatrix& matrix);

private:
    std::size_t flat_index(std::size_t row, std::size_t col) const;
    void ensure_same_dimensions(const RealMatrix& other) const;
    static RealMatrix make_identity(std::size_t size);

    std::size_t rows_{0};
    std::size_t cols_{0};
    double* data_{nullptr};
};

RealMatrix operator+(double scalar, const RealMatrix& matrix);
RealMatrix operator*(double scalar, const RealMatrix& matrix);

}  // namespace lab1

#endif  // LAB1_REAL_MATRIX_H
