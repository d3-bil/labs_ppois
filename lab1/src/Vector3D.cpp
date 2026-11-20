#include "Vector3D.h"

#include <cmath>
#include <stdexcept>

namespace lab1 {

namespace {

bool is_near(double first, double second) {
    return std::fabs(first - second) <= kVectorEpsilon;
}

}  // namespace

bool Point3D::operator==(const Point3D& other) const {
    return is_near(x, other.x) && is_near(y, other.y) && is_near(z, other.z);
}

bool Point3D::operator!=(const Point3D& other) const {
    return !(*this == other);
}

Vector3D::Vector3D(const Point3D& start_point, const Point3D& end_point)
    : start_(start_point), end_(end_point) {}

const Point3D& Vector3D::start_point() const {
    return start_;
}

const Point3D& Vector3D::end_point() const {
    return end_;
}

Point3D Vector3D::displacement() const {
    return Point3D{end_.x - start_.x, end_.y - start_.y, end_.z - start_.z};
}

void Vector3D::apply_displacement(const Point3D& delta) {
    end_.x = start_.x + delta.x;
    end_.y = start_.y + delta.y;
    end_.z = start_.z + delta.z;
}

double Vector3D::length() const {
    const Point3D delta = displacement();
    const double sum_squares = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
    return std::sqrt(sum_squares);
}

double Vector3D::cosine_angle_with(const Vector3D& other) const {
    const double first_length = length();
    const double second_length = other.length();
    if (is_near(first_length, 0.0) || is_near(second_length, 0.0)) {
        throw std::invalid_argument("Cannot compute angle with a zero-length vector.");
    }
    const Point3D first_delta = displacement();
    const Point3D second_delta = other.displacement();
    const double dot_product =
        first_delta.x * second_delta.x +
        first_delta.y * second_delta.y +
        first_delta.z * second_delta.z;
    return dot_product / (first_length * second_length);
}

Vector3D& Vector3D::operator+=(const Vector3D& other) {
    const Point3D current_delta = displacement();
    const Point3D other_delta = other.displacement();
    const Point3D sum_delta{
        current_delta.x + other_delta.x,
        current_delta.y + other_delta.y,
        current_delta.z + other_delta.z
    };
    apply_displacement(sum_delta);
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D& other) const {
    Vector3D result(*this);
    result += other;
    return result;
}

Vector3D& Vector3D::operator-=(const Vector3D& other) {
    const Point3D current_delta = displacement();
    const Point3D other_delta = other.displacement();
    const Point3D diff_delta{
        current_delta.x - other_delta.x,
        current_delta.y - other_delta.y,
        current_delta.z - other_delta.z
    };
    apply_displacement(diff_delta);
    return *this;
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    Vector3D result(*this);
    result -= other;
    return result;
}

Vector3D& Vector3D::operator*=(const Vector3D& other) {
    const Point3D a = displacement();
    const Point3D b = other.displacement();
    const Point3D cross_delta{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    apply_displacement(cross_delta);
    return *this;
}

Vector3D Vector3D::operator*(const Vector3D& other) const {
    Vector3D result(*this);
    result *= other;
    return result;
}

Vector3D& Vector3D::operator*=(double scalar) {
    const Point3D delta = displacement();
    const Point3D scaled_delta{delta.x * scalar, delta.y * scalar, delta.z * scalar};
    apply_displacement(scaled_delta);
    return *this;
}

Vector3D Vector3D::operator*(double scalar) const {
    Vector3D result(*this);
    result *= scalar;
    return result;
}

Vector3D& Vector3D::operator/=(double scalar) {
    if (is_near(scalar, 0.0)) {
        throw std::invalid_argument("Division of vector by zero scalar.");
    }
    return (*this *= (1.0 / scalar));
}

Vector3D Vector3D::operator/(double scalar) const {
    Vector3D result(*this);
    result /= scalar;
    return result;
}

bool Vector3D::operator==(const Vector3D& other) const {
    return start_ == other.start_ && end_ == other.end_;
}

bool Vector3D::operator!=(const Vector3D& other) const {
    return !(*this == other);
}

bool Vector3D::operator>(const Vector3D& other) const {
    return (length() - other.length()) > kVectorEpsilon;
}

bool Vector3D::operator>=(const Vector3D& other) const {
    return !(*this < other);
}

bool Vector3D::operator<(const Vector3D& other) const {
    return (other.length() - length()) > kVectorEpsilon;
}

bool Vector3D::operator<=(const Vector3D& other) const {
    return !(*this > other);
}

std::ostream& operator<<(std::ostream& output, const Vector3D& vector) {
    output << "(" << vector.start_.x << ", " << vector.start_.y << ", " << vector.start_.z
           << ") -> (" << vector.end_.x << ", " << vector.end_.y << ", " << vector.end_.z << ")";
    return output;
}

std::istream& operator>>(std::istream& input, Vector3D& vector) {
    Point3D start_point{};
    Point3D end_point{};
    if (input >> start_point.x >> start_point.y >> start_point.z
              >> end_point.x >> end_point.y >> end_point.z) {
        vector.start_ = start_point;
        vector.end_ = end_point;
    }
    return input;
}

Vector3D operator*(double scalar, const Vector3D& vector) {
    return vector * scalar;
}

}  // namespace lab1
