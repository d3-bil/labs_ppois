#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <stdexcept>

#include "RealMatrix.h"

using Catch::Approx;
using lab1::RealMatrix;

TEST_CASE("RealMatrix addition, subtraction and scalar operations (1.7.2)", "[matrix]") {
    const RealMatrix first(2, 2, 2.0);
    const RealMatrix second(2, 2, 3.0);

    const RealMatrix sum = first + second;
    REQUIRE(sum.at(0, 0) == Approx(5.0));

    const RealMatrix diff = second - first;
    REQUIRE(diff.at(0, 0) == Approx(1.0));

    const RealMatrix plus_scalar = 4.0 + first;
    REQUIRE(plus_scalar.at(1, 1) == Approx(6.0));

    const RealMatrix minus_scalar = first - 1.0;
    REQUIRE(minus_scalar.at(0, 1) == Approx(1.0));

    const RealMatrix scaled = 3.0 * first;
    REQUIRE(scaled.at(0, 0) == Approx(6.0));

    const RealMatrix divided = scaled / 2.0;
    REQUIRE(divided.at(0, 0) == Approx(3.0));
    REQUIRE_THROWS_AS(first / 0.0, std::invalid_argument);

    const RealMatrix wrong_size(3, 2, 1.0);
    REQUIRE_THROWS_AS(first + wrong_size, std::invalid_argument);
}

TEST_CASE("RealMatrix multiplication, power, determinant and norm (1.7.2)", "[matrix]") {
    RealMatrix matrix(2, 2, 0.0);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(1, 0) = 3.0;
    matrix.at(1, 1) = 4.0;

    const RealMatrix squared = matrix ^ 2U;
    REQUIRE(squared.at(0, 0) == Approx(7.0));
    REQUIRE(squared.at(0, 1) == Approx(10.0));
    REQUIRE(squared.at(1, 0) == Approx(15.0));
    REQUIRE(squared.at(1, 1) == Approx(22.0));

    RealMatrix powered(matrix);
    powered ^= 0U;
    REQUIRE(powered.is_identity());

    REQUIRE(matrix.determinant() == Approx(-2.0));
    REQUIRE(matrix.norm() == Approx(std::sqrt(30.0)));

    RealMatrix singular(2, 2, 1.0);
    REQUIRE(singular.determinant() == Approx(0.0));

    const RealMatrix rect(2, 3, 1.0);
    REQUIRE_THROWS_AS(rect.pow(2U), std::invalid_argument);
    REQUIRE_THROWS_AS(rect.determinant(), std::invalid_argument);
    REQUIRE_THROWS_AS(rect * matrix, std::invalid_argument);
}
