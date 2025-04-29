#include <catch2/catch_test_macros.hpp>
#include "Contracts/isp.hpp"

TEST_CASE("Isp class works correctly", "[isp]")
{
    SECTION("Constructor parses input correctly")
    {
        isp person("0549050484");
        CHECK(person.GetYear() == 1905);
        CHECK(person.GetMonth() == 4);
        CHECK(person.GetDay() == 9);
    }

    SECTION("Comparison operators work")
    {
        isp person1("0549050484");
        isp person2("0552012940");

        CHECK(person1 < person2); // 1905 comes before 1952
        CHECK_FALSE(person1 == person2);

        isp person3("0549050484"); // Same as person1
        CHECK(person1 == person3);
        CHECK_FALSE(person1 < person3);
    }
}