#ifndef LAB1_VECTOR3D_H
#define LAB1_VECTOR3D_H

#include <iostream>

namespace lab1 {

/// @brief Точность сравнения вещественных чисел для геометрических вычислений.
constexpr double kVectorEpsilon = 1e-9;

/// @brief Точка в трёхмерном евклидовом пространстве.
struct Point3D {
    double x{0.0};
    double y{0.0};
    double z{0.0};

    bool operator==(const Point3D& other) const;
    bool operator!=(const Point3D& other) const;
};

/// @brief Трёхмерный вектор, заданный координатами начала и конца.
class Vector3D {
public:
    /// @brief Создаёт нулевой вектор в начале координат.
    Vector3D() = default;

    /// @brief Создаёт вектор по координатам начала и конца.
    /// @param start_point Начальная точка вектора.
    /// @param end_point Конечная точка вектора.
    Vector3D(const Point3D& start_point, const Point3D& end_point);

    /// @brief Конструктор копирования.
    Vector3D(const Vector3D& other) = default;

    /// @brief Оператор присваивания копированием.
    Vector3D& operator=(const Vector3D& other) = default;

    /// @brief Деструктор.
    ~Vector3D() = default;

    /// @brief Возвращает начальную точку вектора.
    const Point3D& start_point() const;

    /// @brief Возвращает конечную точку вектора.
    const Point3D& end_point() const;

    /// @brief Вычисляет евклидову длину вектора.
    double length() const;

    /// @brief Вычисляет косинус угла между текущим и переданным вектором.
    /// @throws std::invalid_argument если один из векторов имеет нулевую длину.
    double cosine_angle_with(const Vector3D& other) const;

    Vector3D& operator+=(const Vector3D& other);
    Vector3D operator+(const Vector3D& other) const;

    Vector3D& operator-=(const Vector3D& other);
    Vector3D operator-(const Vector3D& other) const;

    /// @brief Векторное произведение с присваиванием.
    Vector3D& operator*=(const Vector3D& other);

    /// @brief Векторное произведение двух векторов.
    Vector3D operator*(const Vector3D& other) const;

    /// @brief Умножение вектора на скаляр с присваиванием.
    Vector3D& operator*=(double scalar);

    /// @brief Умножение вектора на скаляр.
    Vector3D operator*(double scalar) const;

    /// @brief Деление вектора на скаляр с присваиванием.
    /// @throws std::invalid_argument при делении на ноль.
    Vector3D& operator/=(double scalar);

    /// @brief Деление вектора на скаляр.
    /// @throws std::invalid_argument при делении на ноль.
    Vector3D operator/(double scalar) const;

    bool operator==(const Vector3D& other) const;
    bool operator!=(const Vector3D& other) const;

    bool operator>(const Vector3D& other) const;
    bool operator>=(const Vector3D& other) const;
    bool operator<(const Vector3D& other) const;
    bool operator<=(const Vector3D& other) const;

    /// @brief Запись вектора в поток в формате: (x1, y1, z1) -> (x2, y2, z2).
    friend std::ostream& operator<<(std::ostream& output, const Vector3D& vector);

    /// @brief Чтение шести координат (начало и конец) из потока.
    friend std::istream& operator>>(std::istream& input, Vector3D& vector);

private:
    /// @brief Вспомогательная проекция вектора на оси (dx, dy, dz).
    Point3D displacement() const;

    /// @brief Устанавливает конец вектора относительно текущего начала по смещению.
    void apply_displacement(const Point3D& delta);

    Point3D start_{};
    Point3D end_{};
};

/// @brief Коммутативное умножение скаляра на вектор.
Vector3D operator*(double scalar, const Vector3D& vector);

}  // namespace lab1

#endif  // LAB1_VECTOR3D_H
