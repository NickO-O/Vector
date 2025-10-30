cmake_minimum_required(VERSION 3.14)
project(VectorTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/catch
)

enable_testing()

add_executable(vector_tests tests/tests.cpp)

add_test(NAME vector_tests COMMAND vector_tests)