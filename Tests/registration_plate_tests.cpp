#include <catch2/catch_test_macros.hpp>
#include "Contracts/registration_plate.hpp"
#include <string>
#include <iostream>

TEST_CASE("registration_plate constructor throws on invalid inputs", "[registration_plate]")
{
    SECTION("Empty input")
    {
        CHECK_THROWS_AS(registration_plate(""), std::invalid_argument);
    }

    SECTION("Null input")
    {
        CHECK_THROWS_AS(registration_plate(nullptr), std::invalid_argument);
    }
    
    SECTION("Invalid format")
    {
        CHECK_THROWS_AS(registration_plate("CA12345X"), std::invalid_argument);
        CHECK_THROWS_AS(registration_plate("C123456"), std::invalid_argument);
        CHECK_THROWS_AS(registration_plate("12345AB"), std::invalid_argument);
    }
}

TEST_CASE("String representation", "[registration_plate]")
{
    SECTION("ToString() matches constructor input")
    {
        registration_plate plate1("CA1234BX");
        std::string actual = plate1.to_string();
        REQUIRE(actual == "CA1234BX");
    }
}