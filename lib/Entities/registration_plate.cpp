#include "Contracts/registration_plate.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <fstream>

registration_plate::registration_plate() = default;
registration_plate::registration_plate(const char *plate)
{
    if (!plate || !plate[0])
        throw std::invalid_argument("Invalid input. Expected: XXNNNNXX");

    char *pref = new char[3];
    int num = 0;
    char *suf = new char[3];

    try
    {
        if (sscanf(plate, "%2s%d%2s", pref, &num, suf) != 3)
        {
            delete[] pref;
            delete[] suf;
            throw std::invalid_argument("Invalid format. Expected: XXNNNNXX");
        }

        SetPrefix(std::string(pref));
        SetNumber(num);
        SetSuffix(std::string(suf));
        
        // Free memory after successful parsing
        delete[] pref;
        delete[] suf;
    }
    catch (const std::invalid_argument &e)
    {
        delete[] pref;
        delete[] suf;
        throw; // Re-throw the exception after cleanup
    }
}

void registration_plate::SetPrefix(const std::string &input)
{
    if (input.length() != 2)
        throw std::invalid_argument("Prefix must be exactly 2 characters");

    prefix = input;
}

const std::string registration_plate::GetPrefix() const
{
    return prefix;
}

void registration_plate::SetNumber(int input)
{
    if (input < 1000 || input > 9999)
        throw std::invalid_argument("Number must be 1000-9999");
    number = input;
}

int registration_plate::GetNumber() const
{
    return number;
}

void registration_plate::SetSuffix(const std::string &input)
{
    if (input.length() != 2)
        throw std::invalid_argument("Suffix must be exactly 2 characters");

    suffix = input;
}

const std::string registration_plate::GetSuffix() const
{
    return suffix;
}

bool operator<(const registration_plate &plate1, const registration_plate &plate2)
{
    // Compare prefixes first
    int prefixCmp = plate1.GetPrefix().compare(plate2.GetPrefix());
    if (prefixCmp != 0)
        return prefixCmp < 0;

    // Compare numbers if prefixes are equal
    if (plate1.GetNumber() != plate2.GetNumber())
    {
        return plate1.GetNumber() < plate2.GetNumber();
    }

    // Compare suffixes if everything else is equal
    int suffixCmp = plate1.GetSuffix().compare(plate2.GetSuffix());
    return suffixCmp < 0;
}

std::ostream &operator<<(std::ostream &os, const registration_plate &plate)
{
    os << plate.GetPrefix() << plate.GetNumber() << plate.GetSuffix();
    return os;
}

bool operator==(const registration_plate &plate1, const registration_plate &plate2)
{
    return (plate1.GetPrefix() == plate2.GetPrefix() &&
            plate1.GetNumber() == plate2.GetNumber() &&
            plate1.GetSuffix() == plate2.GetSuffix());
}

const std::string registration_plate::to_string() const
{
    return prefix + std::to_string(number) + suffix;
}