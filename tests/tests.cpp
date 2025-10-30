#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
#include <src/vector.hpp>
#include <string>

TEST_CASE("Just compiles") {
    Vector<std::string> vec;
}


TEST_CASE("Simple test") {
    Vector vec = {1, 2};
    REQUIRE(vec[0] == 1);
    REQUIRE(vec[1] == 2);
}

TEST_CASE("Modify") {
    Vector vec = {1, 2};
    vec[0] = 3;
    REQUIRE(vec[0] == 3);
}


TEST_CASE("A lot of push_backs") {
    size_t size = 1000;
    Vector<int> vec;
    for (size_t i = 0; i < size; ++i) {
        vec.push_back(i);
    }

    for (size_t i = 0; i < size; ++i) {
        REQUIRE(vec[i] == i);
    }
}

TEST_CASE("Copy constructor") {
    Vector<int> vec1 = {3, 4, 1};
    Vector<int> vec2(vec1);
    REQUIRE(vec2[0] == 3);
    REQUIRE(vec2[1] == 4);
    REQUIRE(vec2[2] == 1);
}