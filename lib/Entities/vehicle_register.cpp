#include "Contracts/vehicle_register.hpp"
#include "Contracts/ucn.hpp"
#include "Contracts/registration_plate.hpp"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>

vehicle_register::vehicle_register() = default;

void vehicle_register::Register(registration_plate registration, ucn owner)
{
    auto it = vehicles.find(registration);
    if (it != vehicles.end())
    {
        bool isAlreadyRegisteredPlate = it->first == registration;
        bool isAlreadyAttachedOwner = it->second == owner;
        if (isAlreadyAttachedOwner || isAlreadyRegisteredPlate)
        {

            throw std::invalid_argument("Vehicle is already registered to this owner.");
        }
    }

    vehicles[registration] = owner;

    owner_vehicles[owner].push_back(registration);

    std::cout << "Vehicle " << registration.to_string() << " registered to owner " << owner.to_string() << ".\n";
}

void vehicle_register::deregister(registration_plate registration)
{
    auto it = vehicles.find(registration);
    if (it != vehicles.end())
    {
        ucn owner = it->second;
        vehicles.erase(it);

        auto &owner_list = owner_vehicles[owner];
        owner_list.erase(
            std::remove(owner_list.begin(), owner_list.end(), registration),
            owner_list.end());

        if (owner_list.empty())
        {
            owner_vehicles.erase(owner);
        }
    }
}

std::vector<registration_plate> vehicle_register::owned_vehicles(ucn person) const
{
    auto it = owner_vehicles.find(person);
    if (it != owner_vehicles.end())
    {
        return it->second;
    }
    return std::vector<registration_plate>();
}

std::ostream &operator<<(std::ostream &os, const vehicle_register &reg)
{
    // Output each owner and their vehicles
    for (const auto &pair : reg.vehicles)
    {
        const registration_plate &plate = pair.first;
        const ucn &owner = pair.second;
        os << owner.to_string() << " " << plate.to_string() << "\n";
    }
    return os;
}

std::istream &operator>>(std::istream &is, vehicle_register &reg)
{
    // Clear existing data
    reg.GetVehicles().clear();
    reg.GetOwnerVehicles().clear();

    std::string line;
    while (std::getline(is, line) && !line.empty())
    {
        std::istringstream ss(line);
        std::string owner_str, plate_str;

        // Read owner and plate strings
        if (ss >> owner_str >> plate_str)
        {
            try
            {
                // Parse as ucn and registration_plate
                ucn owner(owner_str.c_str());
                registration_plate plate(plate_str.c_str());

                // Register the vehicle
                reg.Register(plate, owner);
            }
            catch (const std::exception &)
            {
                // If parsing fails, set failbit on stream
                is.setstate(std::ios::failbit);
                break;
            }
        }
        else
        {
            // If format is incorrect, set failbit
            is.setstate(std::ios::failbit);
            break;
        }
    }

    return is;
}