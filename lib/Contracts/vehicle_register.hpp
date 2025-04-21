#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <algorithm>
#include "registration_plate.hpp"
#include "isp.hpp" // Note: using isp instead of ucn based on your file

class vehicle_register
{
private:
    // Maps registration plates to their owners
    std::map<registration_plate, isp> vehicles;

    // Maps owners to their vehicles for quick lookup
    std::map<isp, std::vector<registration_plate>> owner_vehicles;

public:
    vehicle_register(); // constructor

    // Register a vehicle to an owner
    void Register(registration_plate registration, isp owner);

    // Remove a registration
    void deregister(registration_plate registration);

    // Get all vehicles owned by a person
    std::vector<registration_plate> owned_vehicles(isp person) const;

    // Stream operators
    friend std::ostream &operator<<(std::ostream &os, const vehicle_register &reg);
    friend std::istream &operator>>(std::istream &is, vehicle_register &reg);
};