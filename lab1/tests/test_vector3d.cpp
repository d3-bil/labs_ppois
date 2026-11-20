#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <stdexcept>

#include "Vector3D.h"

using Catch::Approx;
using lab1::Point3D;
using lab1::Vector3D;

TEST_CASE("Vector3D endpoints, length and equality", "[vector]") {
    const Vector3D vector({1.0, 2.0, 3.0}, {4.0, 6.0, 3.0});
    REQUIRE(vector.start_point() == Point3D{1.0, 2.0, 3.0});
    REQUIRE(vector.end_point() == Point3D{4.0, 6.0, 3.0});
    REQUIRE(vector.start_point() != vector.end_point());
    REQUIRE(vector.length() == Approx(5.0));

    const Vector3D copy(vector);
    REQUIRE(copy == vector);
    REQUIRE_FALSE(copy != vector);
}

TEST_CASE("Vector3D arithmetic and scalar operations", "[vector]") {
    const Vector3D first({0.0, 0.0, 0.0}, {1.0, 0.0, 0.0});
    const Vector3D second({0.0, 0.0, 0.0}, {0.0, 1.0, 0.0});

    const Vector3D sum = first + second;
    REQUIRE(sum.end_point() == Point3D{1.0, 1.0, 0.0});

    const Vector3D diff = first - second;
    REQUIRE(diff.end_point() == Point3D{1.0, -1.0, 0.0});

    const Vector3D cross = first * second;
    REQUIRE(cross.end_point() == Point3D{0.0, 0.0, 1.0});

    const Vector3D scaled = 3.0 * first;
    REQUIRE(scaled.end_point() == Point3D{3.0, 0.0, 0.0});

    const Vector3D divided = scaled / 3.0;
    REQUIRE(divided == first);
    REQUIRE_THROWS_AS(first / 0.0, std::invalid_argument);
}

TEST_CASE("Vector3D angle cosine, comparisons and stream IO", "[vector]") {
    const Vector3D x_axis({0.0, 0.0, 0.0}, {2.0, 0.0, 0.0});
    const Vector3D y_axis({0.0, 0.0, 0.0}, {0.0, 5.0, 0.0});
    const Vector3D zero_vec;

    REQUIRE(x_axis.cosine_angle_with(y_axis) == Approx(0.0));
    REQUIRE_THROWS_AS(x_axis.cosine_angle_with(zero_vec), std::invalid_argument);

    REQUIRE(y_axis > x_axis);
    REQUIRE(y_axis >= x_axis);
    REQUIRE(x_axis < y_axis);
    REQUIRE(x_axis <= y_axis);

    std::stringstream stream;
    stream << "1 2 3 4 5 6";
    Vector3D parsed;
    stream >> parsed;
    REQUIRE(parsed.start_point() == Point3D{1.0, 2.0, 3.0});
    REQUIRE(parsed.end_point() == Point3D{4.0, 5.0, 6.0});

    std::ostringstream out;
    out << parsed;
    REQUIRE(out.str() == "(1, 2, 3) -> (4, 5, 6)");
}
