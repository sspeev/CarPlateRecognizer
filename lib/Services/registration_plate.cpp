#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <fstream>
#include "Contracts/registration_plate.hpp"

registration_plate::registration_plate(const char *plate) // constructor
    : prefix(nullptr), number(0), suffix(nullptr)
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

        SetPrefix(pref);
        SetNumber(num);
        SetSuffix(suf);
    }
    catch (const std::invalid_argument &e)
    {
        delete[] prefix;
        delete[] suffix;
        prefix = suffix = nullptr;

        std::cerr << "Error: " << e.what() << std::endl;
    }
}

registration_plate::~registration_plate() // destructor
{
    delete[] prefix;
    delete[] suffix;
}

void registration_plate::SetPrefix(const char *input)
{
    if (input && strlen(input) > 2)
        throw std::invalid_argument("Prefix must be 0-2 characters");

    delete[] prefix;
    prefix = nullptr;

    if (input)
    {
        prefix = new char[strlen(input) + 1];
        strcpy(prefix, input);
    }
}

const char *registration_plate::GetPrefix() const
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

void registration_plate::SetSuffix(const char *input)
{
    if (input && strlen(input) > 2)
        throw std::invalid_argument("Suffix must be 0-2 characters");

    delete[] suffix;
    suffix = nullptr;

    if (input)
    {
        suffix = new char[strlen(input) + 1];
        strcpy(suffix, input);
    }
}

const char *registration_plate::GetSuffix() const
{
    return suffix;
}

bool operator<(const registration_plate &plate1, const registration_plate &plate2)
{
    // Compare prefixes first
    if (plate1.GetPrefix() && plate2.GetPrefix())
    {
        int prefixCmp = strcmp(plate1.GetPrefix(), plate2.GetPrefix());
        if (prefixCmp != 0)
            return prefixCmp < 0;
    }
    else if (!plate1.GetPrefix() && plate2.GetPrefix())
    {
        return true;  // null prefix is less than any prefix
    }
    else if (plate1.GetPrefix() && !plate2.GetPrefix())
    {
        return false; // any prefix is greater than null prefix
    }

    // Compare numbers if prefixes are equal
    if (plate1.GetNumber() != plate2.GetNumber())
    {
        return plate1.GetNumber() < plate2.GetNumber();
    }

    // Compare suffixes if everything else is equal
    if (plate1.GetSuffix() && plate2.GetSuffix())
    {
        int suffixCmp = strcmp(plate1.GetSuffix(), plate2.GetSuffix());
        return suffixCmp < 0;
    }
    else if (!plate1.GetSuffix() && plate2.GetSuffix())
    {
        return true;  // null suffix is less than any suffix
    }
    else if (plate1.GetSuffix() && !plate2.GetSuffix())
    {
        return false; // any suffix is greater than null suffix
    }

    return false; // They're equal, so plate1 is not less than plate2
}

std::ostream &operator<<(std::ostream &os, const registration_plate &plate)
{
    if (plate.prefix)
        os << plate.prefix;
    os << plate.number;
    if (plate.suffix)
        os << plate.suffix;
    return os;
}

bool operator==(const registration_plate &plate1, const registration_plate &plate2)
{
    // Compare numbers
    if (plate1.GetNumber() != plate2.GetNumber())
        return false;

    // Compare prefixes
    if ((plate1.GetPrefix() == nullptr) != (plate2.GetPrefix() == nullptr))
        return false;

    if (plate1.GetPrefix() && strcmp(plate1.GetPrefix(), plate2.GetPrefix()) != 0)
        return false;

    // Compare suffixes
    if ((plate1.GetSuffix() == nullptr) != (plate2.GetSuffix() == nullptr))
        return false;

    if (plate1.GetSuffix() && strcmp(plate1.GetSuffix(), plate2.GetSuffix()) != 0)
        return false;

    return true;
}

const std::string registration_plate::to_string() const
{
    return std::string(prefix) + std::to_string(number) + std::string(suffix);
}