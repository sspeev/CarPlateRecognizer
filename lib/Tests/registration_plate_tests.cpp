#include <catch2/catch_test_macros.hpp>
#include "Contracts/registration_plate.hpp"
#include <string>

TEST_CASE("Registration plate class works correctly", "[registration_plate]")
{
    SECTION("Constructor parses input correctly")
    {
        registration_plate plate("CB3408KK");
        CHECK(std::string(plate.GetPrefix()) == "CB");
        CHECK(plate.GetNumber() == 3408);
        CHECK(std::string(plate.GetSuffix()) == "KK");
    }

    SECTION("Comparison operators work")
    {
        registration_plate plate1("CB3408KK");
        registration_plate plate2("CB2858MK");

        CHECK_FALSE(plate1 < plate2); // 3408 > 2858
        CHECK_FALSE(plate1 == plate2);
    }
}