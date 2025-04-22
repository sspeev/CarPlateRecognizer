#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "isp.hpp"
#include "registration_plate.hpp"


class vehicle_register
{
private:
    std::map<registration_plate, isp> vehicles;
    std::map<isp, std::vector<registration_plate>> owner_vehicles;

public:
    vehicle_register();

    void Register(registration_plate registration, isp owner);
    void deregister(registration_plate registration);
    std::vector<registration_plate> owned_vehicles(isp person) const;

    // Accessors for the operator>> function
    std::map<registration_plate, isp> &GetVehicles() { return vehicles; }
    std::map<isp, std::vector<registration_plate>> &GetOwnerVehicles() { return owner_vehicles; }

    friend std::ostream &operator<<(std::ostream &os, const vehicle_register &reg);
    friend std::istream &operator>>(std::istream &is, vehicle_register &reg);
};