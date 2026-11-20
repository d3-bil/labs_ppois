cmake_minimum_required(VERSION 3.20)
project(lab1_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

option(ENABLE_COVERAGE "Enable code coverage flags" ON)
if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

add_library(lab1_core STATIC
    src/Vector3D.cpp
    src/RealMatrixCore.cpp
    src/RealMatrixProperties.cpp
    src/RealMatrixAlgebra.cpp
)
target_include_directories(lab1_core PUBLIC include)

add_executable(lab1_cli
    src/CliMenu.cpp
    src/main.cpp
)
target_link_libraries(lab1_cli PRIVATE lab1_core)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_executable(lab1_tests
    tests/test_vector3d.cpp
    tests/test_matrix_properties.cpp
    tests/test_matrix_algebra.cpp
)
target_link_libraries(lab1_tests PRIVATE lab1_core Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(lab1_tests)
