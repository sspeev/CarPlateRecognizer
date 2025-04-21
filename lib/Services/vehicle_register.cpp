#include "../Contracts/vehicle_register.hpp"
#include <sstream>

class vehicle_register
{
public:
    vehicle_register();

    void Register(registration_plate registration, isp owner);
    void deregister(registration_plate registration);
    std::vector<registration_plate> owned_vehicles(isp person) const;

    friend std::ostream &operator<<(std::ostream &os, const vehicle_register &reg);
    friend std::istream &operator>>(std::istream &is, vehicle_register &reg);

private:
    std::map<registration_plate, isp> vehicles;
    std::map<isp, std::vector<registration_plate>> owner_vehicles;
};

vehicle_register::vehicle_register()
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

    // Register the vehicle to this owner
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

std::vector<registration_plate> vehicle_register::owned_vehicles(isp person) const
{
    // Look up the person in the owner_vehicles map
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
    // Output each registration in the required format
    for (const auto &[plate, owner] : reg.vehicles)
    {
        os << owner.to_string() << " " << plate.to_string() << '\n';
    }
    return os;
}

std::istream &operator>>(std::istream &is, vehicle_register &reg)
{
    // Clear existing data
    reg.vehicles.clear();
    reg.owner_vehicles.clear();

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
                // Skip invalid entries
                continue;
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