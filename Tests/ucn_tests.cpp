#include <catch2/catch_test_macros.hpp>
#include "Contracts/ucn.hpp"
#include <iostream>


TEST_CASE("ucn constructor handles valid inputs", "[ucn]")
{
    SECTION("2000s birthdate (month > 40)")
    {
        ucn person("0549050484");
        REQUIRE(person.GetYear() == 2005);
        REQUIRE(person.GetMonth() == 9);
        REQUIRE(person.GetDay() == 5);
        REQUIRE(person.GetRegion() == "Burgas");
    }

    SECTION("1999s birthdate (month is the actual month)")
    {
        ucn person("9912316334");
        REQUIRE(person.GetYear() == 1999);
        REQUIRE(person.GetMonth() == 12);
        REQUIRE(person.GetDay() == 31);
        REQUIRE(person.GetRegion() == "Sofia-grad");
    }
}


TEST_CASE("ucn constructor throws on invalid inputs", "[ucn]")
{
    SECTION("Invalid UCN format")
    {
        CHECK_THROWS_AS(ucn("0549050483"), std::invalid_argument);
    }

    SECTION("Empty input")
    {
        CHECK_THROWS_AS(ucn(""), std::invalid_argument);
    }

    SECTION("Null input")
    {
        CHECK_THROWS_AS(ucn(nullptr), std::invalid_argument);
    }
}


TEST_CASE("Comparison operators work correctly", "[isp]")
{
    SECTION("Less than operator")
    {
        ucn person1("8508092027");
        ucn person2("0549050484");
        REQUIRE(person2 < person1);
        REQUIRE_FALSE(person1 < person2);
    }

    SECTION("Same year, different month")
    {
        ucn person1("8507102136");
        ucn person2("8508092027");

        REQUIRE(person2 < person1);
        REQUIRE_FALSE(person1 < person2);
    }

    SECTION("Same year and month, different day")
    {
        ucn person1("8507102136");
        ucn person2("8507110635");

        REQUIRE(person2 < person1);
        REQUIRE_FALSE(person1 < person2);
    }

    SECTION("Equality operator")
    {
        ucn person1("0549050484");
        ucn person2("0549050484");

        REQUIRE(person1 == person2);
    }
}


TEST_CASE("UCN string validation", "[ucn]")
{
    SECTION("Non-numeric characters")
    {
        CHECK_THROWS_AS(ucn("123456789A"), std::invalid_argument);
    }

    SECTION("Incorrect length")
    {
        CHECK_THROWS_AS(ucn("12345"), std::invalid_argument);
        CHECK_THROWS_AS(ucn("12345678901"), std::invalid_argument);
    }

    SECTION("Invalid date components")
    {
        // Invalid month (> 12 for 1900s, > 52 for 2000s)
        CHECK_THROWS_AS(ucn("9913316334"), std::invalid_argument);
        CHECK_THROWS_AS(ucn("0553050484"), std::invalid_argument);
        
        // Invalid day (> 31)
        CHECK_THROWS_AS(ucn("9912326334"), std::invalid_argument);
        CHECK_THROWS_AS(ucn("0549320484"), std::invalid_argument);
        
        // Invalid date (February 30th)
        CHECK_THROWS_AS(ucn("9902306334"), std::invalid_argument);
        CHECK_THROWS_AS(ucn("0542306334"), std::invalid_argument);
    }

    SECTION("Invalid checksum")
    {
        CHECK_THROWS_AS(ucn("0549050480"), std::invalid_argument);
    }
}


TEST_CASE("Region calculation works correctly", "[ucn]")
{
    SECTION("Various region codes")
    {
        ucn person1("0549050442");
        REQUIRE(person1.GetRegion() == "Burgas");

        ucn person2("0549052825");
        REQUIRE(person2.GetRegion() == "Kyustendil");

        ucn person3("0549051069"); 
        REQUIRE(person3.GetRegion() == "Varna");

        ucn person4("0549056353"); 
        REQUIRE(person4.GetRegion() == "Sofia-grad");
    }
}


TEST_CASE("Copy constructor and assignment", "[ucn]")
{
    SECTION("Copy constructor")
    {
        ucn original("0549050484");
        ucn copy(original);

        REQUIRE(copy.GetYear() == 2005);
        REQUIRE(copy.GetMonth() == 9);
        REQUIRE(copy.GetDay() == 5);
        REQUIRE(copy.GetRegion() == "Burgas");
        REQUIRE(copy == original);
    }

    SECTION("Assignment operator")
    {
        ucn original("0549050484");
        ucn assigned("9912316334");
        
        assigned = original;

        REQUIRE(assigned.GetYear() == 2005);
        REQUIRE(assigned.GetMonth() == 9);
        REQUIRE(assigned.GetDay() == 5);
        REQUIRE(assigned.GetRegion() == "Burgas");
        REQUIRE(assigned == original);
    }
}


TEST_CASE("Move semantics", "[ucn]")
{
    SECTION("Move constructor")
    {
        ucn original("0549050484");
        ucn moved(std::move(original));

        REQUIRE(moved.GetYear() == 2005);
        REQUIRE(moved.GetMonth() == 9);
        REQUIRE(moved.GetDay() == 5);
        REQUIRE(moved.GetRegion() == "Burgas");
    }

    SECTION("Move assignment")
    {
        ucn original("0549050484");
        ucn moved("9912316334");
        
        moved = std::move(original);

        REQUIRE(moved.GetYear() == 2005);
        REQUIRE(moved.GetMonth() == 9);
        REQUIRE(moved.GetDay() == 5);
        REQUIRE(moved.GetRegion() == "Burgas");
    }
}


TEST_CASE("Edge case birth dates", "[ucn]")
{
    SECTION("Leap year February 29")
    {
        ucn person("0042293165"); // February 29, 2000 (leap year)
        REQUIRE(person.GetYear() == 2000);
        REQUIRE(person.GetMonth() == 2);
        REQUIRE(person.GetDay() == 29);
    }

    SECTION("Different centuries")
    {
        ucn person1("0042293165"); // 2000
        ucn person2("9902201045"); // 1999
        ucn person3("0102200418"); // 1901

        REQUIRE(person1 < person2);
        REQUIRE(person2 < person3);
    }
}