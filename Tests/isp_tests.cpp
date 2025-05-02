#include <catch2/catch_test_macros.hpp>
#include "Contracts/isp.hpp"

// TEST_CASE("Isp class works correctly", "[isp]")
// {
//     SECTION("Constructor parses input correctly")
//     {
//         isp person("0549050484");
//         CHECK(person.GetYear() == 2005);
//         CHECK(person.GetMonth() == 9);
//         CHECK(person.GetDay() == 5);
//     }

//     SECTION("Comparison operators work")
//     {
//         isp person1("0549050484");
//         isp person2("0552012940");

//         CHECK(person1 < person2); // 1905 comes before 1952
//         CHECK_FALSE(person1 == person2);

//         isp person3("0549050484"); // Same as person1
//         CHECK(person1 == person3);
//         CHECK_FALSE(person1 < person3);
//     }
// }

TEST_CASE("isp::isp() parses the EGN correctly", "[isp]")
{
    SECTION("Valid EGN")
    {
        isp person("0549050484");
        REQUIRE(person.GetYear() == 2005);
        REQUIRE(person.GetMonth() == 9);
        REQUIRE(person.GetDay() == 5);
        REQUIRE(person.GetRegion() == "Burgas");
    }
    SECTION("Invalid EGN")
    {
        REQUIRE_THROWS_AS(isp("1234567890"), std::invalid_argument);
    }
}