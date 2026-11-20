#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "RealMatrix.h"

using Catch::Approx;
using lab1::RealMatrix;

TEST_CASE("RealMatrix core lifecycle, indexing and inc/dec", "[matrix]") {
    RealMatrix matrix(2, 2, 1.0);
    REQUIRE(matrix.rows() == 2);
    REQUIRE(matrix.cols() == 2);
    REQUIRE_THROWS_AS(matrix.at(5, 0), std::out_of_range);

    const RealMatrix post_inc = matrix++;
    REQUIRE(post_inc.at(0, 0) == Approx(1.0));
    REQUIRE(matrix.at(0, 0) == Approx(2.0));

    const RealMatrix post_dec = matrix--;
    REQUIRE(post_dec.at(0, 0) == Approx(2.0));
    REQUIRE(matrix.at(0, 0) == Approx(1.0));

    RealMatrix assigned;
    assigned = matrix;
    REQUIRE(assigned == matrix);
    assigned.at(0, 0) = 9.0;
    REQUIRE(assigned != matrix);
}

TEST_CASE("RealMatrix properties and transpose (1.7.1)", "[matrix]") {
    RealMatrix identity(2, 2, 0.0);
    identity.at(0, 0) = 1.0;
    identity.at(1, 1) = 1.0;

    REQUIRE(identity.is_square());
    REQUIRE(identity.is_diagonal());
    REQUIRE(identity.is_identity());
    REQUIRE(identity.is_symmetric());
    REQUIRE(identity.is_upper_triangular());
    REQUIRE(identity.is_lower_triangular());
    REQUIRE_FALSE(identity.is_zero());

    const RealMatrix zero(2, 3, 0.0);
    REQUIRE(zero.is_zero());
    REQUIRE_FALSE(zero.is_square());
    REQUIRE_FALSE(zero.is_diagonal());
    REQUIRE_FALSE(zero.is_symmetric());
    REQUIRE_FALSE(zero.is_upper_triangular());
    REQUIRE_FALSE(zero.is_lower_triangular());

    RealMatrix rect(2, 3, 0.0);
    rect.at(0, 2) = 7.0;
    const RealMatrix transposed = rect.transpose();
    REQUIRE(transposed.rows() == 3);
    REQUIRE(transposed.cols() == 2);
    REQUIRE(transposed.at(2, 0) == Approx(7.0));
}

TEST_CASE("RealMatrix resize, submatrix and file loading (1.7.1)", "[matrix]") {
    RealMatrix matrix(2, 2, 3.0);
    matrix.resize(3, 3, 5.0);
    REQUIRE(matrix.at(0, 0) == Approx(3.0));
    REQUIRE(matrix.at(2, 2) == Approx(5.0));

    const RealMatrix sub = matrix.extract_submatrix(1, 1, 2, 2);
    REQUIRE(sub.rows() == 2);
    REQUIRE(sub.at(0, 0) == Approx(3.0));
    REQUIRE(sub.at(1, 1) == Approx(5.0));
    REQUIRE_THROWS_AS(matrix.extract_submatrix(2, 2, 2, 2), std::out_of_range);

    const std::string temp_file = "test_matrix_tmp.txt";
    {
        std::ofstream out(temp_file);
        out << matrix;
    }
    RealMatrix loaded;
    loaded.load_from_file(temp_file);
    REQUIRE(loaded == matrix);
    std::remove(temp_file.c_str());

    REQUIRE_THROWS_AS(loaded.load_from_file("non_existent_file.txt"), std::runtime_error);
}
