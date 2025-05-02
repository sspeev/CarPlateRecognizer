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
        return;

    char *pref = new char[3];
    int num = 0;
    char *suf = new char[3];

    try
    {
        if (sscanf(plate, "%2s%d%2s", pref, &num, suf) != 3)
            throw std::invalid_argument("Invalid format. Expected: XXNNNNXX");

        SetPrefix(std::string(pref));
        SetNumber(num);
        SetSuffix(std::string(suf));
    }
    catch (const std::invalid_argument &e)
    {
        delete[] pref;
        delete[] suf;
        pref = nullptr;
        suf = nullptr;

        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void registration_plate::SetPrefix(const std::string &input)
{
    if (input.length() > 2)
        throw std::invalid_argument("Prefix must be 0-2 characters");

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
    if (input.length() > 2)
        throw std::invalid_argument("Suffix must be 0-2 characters");

    suffix = input;
}

const std::string registration_plate::GetSuffix() const
{
    return suffix;
}

bool operator<(const registration_plate &plate1, const registration_plate &plate2)
{
    // Compare prefixes first
    if (plate1.GetPrefix() != "" && plate2.GetPrefix() != "")
    {
        int prefixCmp = plate1.GetPrefix().compare(plate2.GetPrefix());
        if (prefixCmp != 0)
            return prefixCmp < 0;
    }
    else if (plate1.GetPrefix() == "" && plate2.GetPrefix() != "")
    {
        return true;  // null prefix is less than any prefix
    }
    else if (plate1.GetPrefix() != "" && plate2.GetPrefix() == "")
    {
        return false; // any prefix is greater than null prefix
    }

    // Compare numbers if prefixes are equal
    if (plate1.GetNumber() != plate2.GetNumber())
    {
        return plate1.GetNumber() < plate2.GetNumber();
    }

    // Compare suffixes if everything else is equal
    if (plate1.GetSuffix() != "" && plate2.GetSuffix() != "")
    {
        int suffixCmp = plate1.GetPrefix().compare(plate2.GetPrefix());
        return suffixCmp < 0;
    }
    else if (plate1.GetSuffix() == "" && plate2.GetSuffix() != "")
    {
        return true;  // null suffix is less than any suffix
    }
    else if (plate1.GetSuffix() != "" && plate2.GetSuffix() == "")
    {
        return false; // any suffix is greater than null suffix
    }

    return false; // They're equal, so plate1 is not less than plate2
}

std::ostream &operator<<(std::ostream &os, const registration_plate &plate)
{
    if (plate.prefix != "")
        os << plate.prefix;
    os << plate.number;
    if (plate.suffix != "")
        os << plate.suffix;
    return os;
}

bool operator==(const registration_plate &plate1, const registration_plate &plate2)
{
    // Compare numbers
    if (plate1.GetNumber() != plate2.GetNumber())
        return false;

    // Compare prefixes
    if ((plate1.GetPrefix() == "") != (plate2.GetPrefix() == ""))
        return false;

    if (plate1.GetPrefix() != "" && plate1.GetPrefix().compare(plate2.GetPrefix()) != 0)
        return false;

    // Compare suffixes
    if ((plate1.GetSuffix() == "") != (plate2.GetSuffix() == ""))
        return false;

    if (plate1.GetSuffix() != "" && plate1.GetSuffix().compare(plate2.GetSuffix()) != 0)
        return false;

    return true;
}

const std::string registration_plate::to_string() const
{
    return prefix + std::to_string(number) + suffix;
}