#include "Contracts/vehicle_register.hpp"
#include "Contracts/ucn.hpp"
#include "Contracts/registration_plate.hpp"
#include <vector>
#include <sstream>
#include <string>

vehicle_register::vehicle_register() = default;

void vehicle_register::Register(registration_plate registration, ucn owner)
{
    // Check if the vehicle is already registered to any owner
    auto it = vehicles.find(registration);
    if (it != vehicles.end())
    {
        // Vehicle is already registered
        if (!(it->second == owner))
        {
            // Cannot register to a different owner
            throw std::invalid_argument("Vehicle is already registered to another owner");
        }
        else
        {
            // Cannot register to the same owner twice
            throw std::invalid_argument("Vehicle is already registered to this owner");
        }
    }

    // Register the vehicle to the owner
    vehicles[registration] = owner;

    // Add to the owner's list of vehicles
    owner_vehicles[owner].push_back(registration);
}

void vehicle_register::deregister(registration_plate registration)
{
    // Find the vehicle in the registry
    auto it = vehicles.find(registration);
    if (it != vehicles.end())
    {
        // Get the owner of the vehicle
        ucn owner = it->second;

        // Remove the vehicle from the registry
        vehicles.erase(it);

        // Find the vehicle in the owner's list and remove it
        auto &owner_list = owner_vehicles[owner];
        owner_list.erase(
            std::remove(owner_list.begin(), owner_list.end(), registration),
            owner_list.end());

        // If the owner has no more vehicles, remove the owner entry
        if (owner_list.empty())
        {
            owner_vehicles.erase(owner);
        }
    }
    // Silently ignore if the vehicle is not registered (as specified in the test)
}

// Look up the person in the owner_vehicles map
std::vector<registration_plate> vehicle_register::owned_vehicles(ucn person) const
{
    auto it = owner_vehicles.find(person);
    if (it != owner_vehicles.end())
    {
        return it->second;
    }
    return std::vector<registration_plate>(); // Return empty vector if owner not found
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