#include "Contracts/vehicle_register.hpp"
#include "Contracts/isp.hpp"
#include "Contracts/registration_plate.hpp"
#include <vector>
#include <sstream>
#include <string>

vehicle_register::vehicle_register()//constructor
    : vehicles(), owner_vehicles()
{
    // Empty constructor creates empty maps
}

void vehicle_register::Register(registration_plate registration, isp owner)
{
    // Check if the vehicle is already registered to a different owner
    auto it = vehicles.find(registration);
    if (it != vehicles.end())
    {
        // Compare ISP numbers - if they're not the same, throw exception
        if (!(it->second.GetYear() == owner.GetYear() &&
              it->second.GetMonth() == owner.GetMonth() &&
              it->second.GetDay() == owner.GetDay() &&
              it->second.GetRegion() == owner.GetRegion()))
        {
            throw std::invalid_argument("Vehicle is already registered to another owner");
        }
    }

    else
    {
        // If the vehicle is not registered, check if the owner already has it
        auto &owner_list = owner_vehicles[owner];
        if (std::find(owner_list.begin(), owner_list.end(), registration) != owner_list.end())
        {
            throw std::invalid_argument("Vehicle is already registered to this owner");
        }
    }

    vehicles[registration] = owner;

    // Add to the owner's list of vehicles
    owner_vehicles[owner].push_back(registration);
}

void vehicle_register::deregister(registration_plate registration)
{
    // Find the vehicle in the map
    auto it = vehicles.find(registration);
    if (it != vehicles.end())
    {
        // Get the current owner
        isp owner = it->second;

        // Remove from the owner's list of vehicles
        auto &owner_list = owner_vehicles[owner];
        auto vehicle_it = std::find(owner_list.begin(), owner_list.end(), registration);
        if (vehicle_it != owner_list.end())
        {
            owner_list.erase(vehicle_it);
        }

        // If the owner no longer has any vehicles, remove from the map
        if (owner_list.empty())
        {
            owner_vehicles.erase(owner);
        }

        // Remove the vehicle registration
        vehicles.erase(it);
    }
}

// Look up the person in the owner_vehicles map
std::vector<registration_plate> vehicle_register::owned_vehicles(isp person) const
{
    auto it = owner_vehicles.find(person);
    if (it != owner_vehicles.end())
    {
        return it->second;
    }

    // Return empty vector if not found
    return {};
}

std::ostream &operator<<(std::ostream &os, const vehicle_register &reg)
{
    for (const auto &[plate, owner_const_ref] : reg.vehicles)
    {
        isp owner = owner_const_ref;
        os << owner.to_string() << " " << plate.to_string() << '\n';
    }
    return os;
}


//REVIEW
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
                // Parse as isp and registration_plate
                isp owner(owner_str.c_str());
                registration_plate plate(plate_str.c_str());

                // Register the vehicle
                reg.Register(plate, owner);
            }
            catch (const std::exception &e)
            {
                // Handle parsing errors
                std::cerr << "Error: " << e.what() << '\n';
                is.setstate(std::ios::failbit); // Set failbit on stream
                break; // Exit loop on error
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