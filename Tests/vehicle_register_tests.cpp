#include <catch2/catch_test_macros.hpp>
#include "Contracts/vehicle_register.hpp"
#include <iostream>
#include <sstream>

TEST_CASE("vehicle_register can register vehicles to owners", "[vehicle_register]")
{
    vehicle_register reg;

    SECTION("Register a vehicle to an owner")
    {
        registration_plate plate("CA1234AB");
        ucn owner("0102200418");
        REQUIRE_NOTHROW(reg.Register(plate, owner));

        auto vehicles = reg.owned_vehicles(owner);
        REQUIRE(vehicles.size() == 1);
        REQUIRE(vehicles[0].to_string() == plate.to_string());
    }

    SECTION("Cannot register the same vehicle to a different owner")
    {
        registration_plate plate("CA5678CD");
        ucn owner1("7502202275");
        ucn owner2("8902201423");

        REQUIRE_NOTHROW(reg.Register(plate, owner1));
        REQUIRE_THROWS_AS(reg.Register(plate, owner2), std::invalid_argument);

        // Vehicle should still be registered to the first owner
        auto vehicles = reg.owned_vehicles(owner1);
        REQUIRE(vehicles.size() == 1);
        REQUIRE(vehicles[0].to_string() == plate.to_string());
    }

    SECTION("Cannot register the same vehicle to the same owner twice")
    {
        registration_plate plate("CB9876EF");
        ucn owner("9202201179");

        REQUIRE_NOTHROW(reg.Register(plate, owner));
        REQUIRE_THROWS_AS(reg.Register(plate, owner), std::invalid_argument);

        // Owner should still have only one vehicle
        auto vehicles = reg.owned_vehicles(owner);
        REQUIRE(vehicles.size() == 1);
    }

    SECTION("Owner can register multiple vehicles")
    {
        registration_plate plate1("CC1122GH");
        registration_plate plate2("CC3344IJ");
        registration_plate plate3("CC5566KL");
        ucn owner("8802200167");

        REQUIRE_NOTHROW(reg.Register(plate1, owner));
        REQUIRE_NOTHROW(reg.Register(plate2, owner));
        REQUIRE_NOTHROW(reg.Register(plate3, owner));

        auto vehicles = reg.owned_vehicles(owner);
        REQUIRE(vehicles.size() == 3);

        // Check if all vehicles are registered
        bool found1 = false, found2 = false, found3 = false;
        for (const auto &plate : vehicles)
        {
            if (plate.to_string() == plate1.to_string())
                found1 = true;
            if (plate.to_string() == plate2.to_string())
                found2 = true;
            if (plate.to_string() == plate3.to_string())
                found3 = true;
        }

        REQUIRE(found1);
        REQUIRE(found2);
        REQUIRE(found3);
    }
}

TEST_CASE("vehicle_register can deregister vehicles", "[vehicle_register]")
{
    vehicle_register reg;

    SECTION("Deregister an existing vehicle")
    {
        registration_plate plate("CA1234AB");
        ucn owner("8802200167");

        reg.Register(plate, owner);
        REQUIRE_NOTHROW(reg.deregister(plate));

        // Owner should have no vehicles
        auto vehicles = reg.owned_vehicles(owner);
        REQUIRE(vehicles.empty());
    }

    SECTION("Deregister one of multiple vehicles")
    {
        registration_plate plate1("CB1111AA");
        registration_plate plate2("CB2222BB");
        ucn owner("8802202025");

        reg.Register(plate1, owner);
        reg.Register(plate2, owner);

        REQUIRE_NOTHROW(reg.deregister(plate1));

        // Owner should still have one vehicle
        auto vehicles = reg.owned_vehicles(owner);
        REQUIRE(vehicles.size() == 1);
        REQUIRE(vehicles[0].to_string() == plate2.to_string());
    }

    SECTION("Deregistering a non-existent vehicle doesn't throw")
    {
        registration_plate plate("CC9999ZZ");
        REQUIRE_NOTHROW(reg.deregister(plate));
    }

    SECTION("Owner is removed when all vehicles are deregistered")
    {
        registration_plate plate("CD1234EF");
        ucn owner("8802205831");

        reg.Register(plate, owner);
        reg.deregister(plate);

        // Owner should have no vehicles
        auto vehicles = reg.owned_vehicles(owner);
        REQUIRE(vehicles.empty());

        // Owner's entry should be removed from the owner_vehicles map
        REQUIRE(reg.GetOwnerVehicles().find(owner) == reg.GetOwnerVehicles().end());
    }
}

TEST_CASE("vehicle_register can find vehicles owned by a person", "[vehicle_register]")
{
    vehicle_register reg;

    SECTION("owned_vehicles returns empty vector for non-existent owner")
    {
        ucn owner("8109050649");
        auto vehicles = reg.owned_vehicles(owner);
        REQUIRE(vehicles.empty());
    }

    SECTION("owned_vehicles returns correct list for existing owner")
    {
        registration_plate plate1("CE1010GH");
        registration_plate plate2("CE2020IJ");
        ucn owner("8509053072");

        reg.Register(plate1, owner);
        reg.Register(plate2, owner);

        auto vehicles = reg.owned_vehicles(owner);
        REQUIRE(vehicles.size() == 2);

        bool found1 = false, found2 = false;
        for (const auto &plate : vehicles)
        {
            if (plate.to_string() == plate1.to_string())
                found1 = true;
            if (plate.to_string() == plate2.to_string())
                found2 = true;
        }

        REQUIRE(found1);
        REQUIRE(found2);
    }
}

TEST_CASE("vehicle_register input/output operations", "[vehicle_register]")
{
    SECTION("Output operator writes correct format")
    {
        vehicle_register reg;
        registration_plate plate1("CF1234KL");
        registration_plate plate2("CF5678MN");
        ucn owner1("9009050652");
        ucn owner2("3006138939");

        reg.Register(plate1, owner1);
        reg.Register(plate2, owner2);

        std::stringstream ss;
        ss << reg;

        std::string output = ss.str();
        REQUIRE(output.find(owner1.to_string() + " " + plate1.to_string()) != std::string::npos);
        REQUIRE(output.find(owner2.to_string() + " " + plate2.to_string()) != std::string::npos);
    }

    SECTION("Input operator reads correct format")
    {
        vehicle_register reg;
        std::stringstream ss;
        ss << "9009050652 CF1234KL\n";
        ss << "3006138939 CF5678MN\n";

        ss >> reg;

        ucn owner1("9009050652");
        ucn owner2("3006138939");

        auto vehicles1 = reg.owned_vehicles(owner1);
        auto vehicles2 = reg.owned_vehicles(owner2);

        REQUIRE(vehicles1.size() == 1);
        REQUIRE(vehicles2.size() == 1);

        REQUIRE(vehicles1[0].to_string() == "CF1234KL");
        REQUIRE(vehicles2[0].to_string() == "CF5678MN");
    }

    SECTION("Input operator handles invalid input")
    {
        vehicle_register reg;
        std::stringstream ss;
        ss << "invalid_ucn invalid_plate\n";

        ss >> reg;

        REQUIRE(ss.fail());
        REQUIRE(reg.GetVehicles().empty());
        REQUIRE(reg.GetOwnerVehicles().empty());
    }
}
