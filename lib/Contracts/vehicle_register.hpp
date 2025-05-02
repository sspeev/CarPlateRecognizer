#include "ucn.hpp"
#include "registration_plate.hpp"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>

class vehicle_register
{
private:
    std::map<registration_plate, ucn> vehicles;
    std::map<ucn, std::vector<registration_plate>> owner_vehicles;

public:
    vehicle_register();

    void Register(registration_plate registration, ucn owner);
    void deregister(registration_plate registration);
    std::vector<registration_plate> owned_vehicles(ucn person) const;

    // Accessors for the operator>> function
    std::map<registration_plate, ucn> &GetVehicles() { return vehicles; }
    std::map<ucn, std::vector<registration_plate>> &GetOwnerVehicles() { return owner_vehicles; }

    friend std::ostream &operator<<(std::ostream &os, const vehicle_register &reg);
    friend std::istream &operator>>(std::istream &is, vehicle_register &reg);
};