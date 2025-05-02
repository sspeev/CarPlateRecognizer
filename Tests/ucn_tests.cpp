#include <catch2/catch_test_macros.hpp>
#include "Contracts/ucn.hpp"
#include <iostream>

TEST_CASE("ucn constructor handles valid inputs", "[ucn]")
{
    SECTION("1900s birthdate (month <= 12)")
    {
        ucn person("5503125892");
        REQUIRE(person.GetYear() == 1955);
        REQUIRE(person.GetMonth() == 3);
        REQUIRE(person.GetDay() == 12);
    }

    SECTION("2000s birthdate (month > 40)")
    {
        ucn person("0549050484");
        REQUIRE(person.GetYear() == 2005);
        REQUIRE(person.GetMonth() == 9);
        REQUIRE(person.GetDay() == 5);
        REQUIRE(person.GetRegion() == "Burgas");
    }

    SECTION("Edge case birth month")
    {
        ucn person("0152313456"); // January 2001
        REQUIRE(person.GetYear() == 2001);
        REQUIRE(person.GetMonth() == 12);
        REQUIRE(person.GetDay() == 31);
    }
}

TEST_CASE("ucn constructor throws on invalid inputs", "[ucn]")
{
    SECTION("Invalid format")
    {
        REQUIRE_THROWS_AS(ucn("1234567890"), std::invalid_argument);
    }

    SECTION("Empty input")
    {
        REQUIRE_THROWS_AS(ucn(""), std::invalid_argument);
    }

    SECTION("Null input")
    {
        REQUIRE_THROWS_AS(ucn(nullptr), std::invalid_argument);
    }
}
/*
TEST_CASE("Region calculation works correctly", "[ucn]")
{
    SECTION("Various region codes")
    {
        isp person1("0549050484"); // Region 048 - Burgas
        REQUIRE(person1.GetRegion() == "Burgas");

        isp person2("0549050684"); // Region 068 - Burgas
        REQUIRE(person2.GetRegion() == "Burgas");

        isp person3("0549051004"); // Region 100 - Varna
        REQUIRE(person3.GetRegion() == "Varna");

        isp person4("0549056504"); // Region 650 - Sofia-grad
        REQUIRE(person4.GetRegion() == "Sofia-grad");
    }
}

TEST_CASE("Comparison operators work correctly", "[isp]")
{
    SECTION("Less than operator")
    {
        isp person1("5503125892"); // 1955
        isp person2("0549050484"); // 2005

        REQUIRE(person1 < person2);
        REQUIRE_FALSE(person2 < person1);
    }

    SECTION("Same year, different month")
    {
        isp person1("0501050484"); // January 2005
        isp person2("0549050484"); // September 2005

        REQUIRE(person1 < person2);
        REQUIRE_FALSE(person2 < person1);
    }

    SECTION("Same year and month, different day")
    {
        isp person1("0549020484"); // September 2, 2005
        isp person2("0549050484"); // September 5, 2005

        REQUIRE(person1 < person2);
        REQUIRE_FALSE(person2 < person1);
    }

    SECTION("Equality operator")
    {
        isp person1("0549050484");
        isp person2("0549050484");
        isp person3("0549050485"); // Different last digit

        REQUIRE(person1 == person2);
        REQUIRE_FALSE(person1 == person3);
    }
}

TEST_CASE("Stream operators work correctly", "[isp]")
{
    SECTION("Output stream")
    {
        isp person("0549050484");
        std::stringstream ss;
        ss << person;
        REQUIRE(ss.str() == "592005"); // day + month + year
    }

    SECTION("Input stream with valid input")
    {
        std::stringstream ss("0549050484");
        isp person;
        ss >> person;
        REQUIRE(person.GetYear() == 2005);
        REQUIRE(person.GetMonth() == 9);
        REQUIRE(person.GetDay() == 5);
    }

    SECTION("Input stream with invalid input")
    {
        std::stringstream ss("invalid");
        isp person;
        ss >> person;
        REQUIRE(ss.fail());
    }
}

TEST_CASE("to_string method works correctly", "[isp]")
{
    SECTION("Valid isp to string")
    {
        isp person("0549050484");
        std::string str = person.to_string();
        REQUIRE(str.length() == 10);
        // Note: Need to account for how the method formats the year
        // The actual formatted year might be different than the original input
    }
}

*/