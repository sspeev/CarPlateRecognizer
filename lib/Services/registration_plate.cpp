#include <iostream>
#include <stdexcept>
#include <cstring>
#include <fstream>
#include "../Contracts/registration_plate.hpp"

registration_plate::registration_plate(const char *plate) // constructor
    : prefix(nullptr), number(0), suffix(nullptr)
{
    if (!plate || !plate[0])
        return;

    char pref[3] = {0};
    int num = 0;
    char suf[3] = {0};

    if (sscanf(plate, "%2s%d%2s", pref, &num, suf) != 3)
        throw std::invalid_argument("Invalid format. Expected: XXNNNNXX");

    try
    {
        SetPrefix(pref);
        SetNumber(num);
        SetSuffix(suf);
    }
    catch (const std::invalid_argument &e)
    {
        delete[] prefix;
        delete[] suffix;
        prefix = suffix = nullptr;
        throw;
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

const registration_plate operator<(const registration_plate &plate1, const registration_plate &plate2)
{
    // Compare prefixes first
    if (plate1.GetPrefix() && plate2.GetPrefix())
    {
        int prefixCmp = strcmp(plate1.GetPrefix(), plate2.GetPrefix());
        if (prefixCmp != 0)
            return prefixCmp < 0 ? plate1 : plate2;
    }
    else if (plate1.GetPrefix())
    {
        return plate2;
    }
    else if (plate2.GetPrefix())
    {
        return plate1;
    }

    // Compare numbers if prefixes are equal
    if (plate1.GetNumber() != plate2.GetNumber())
    {
        return plate1.GetNumber() < plate2.GetNumber() ? plate1 : plate2;
    }

    // Compare suffixes if everything else is equal
    if (plate1.GetSuffix() && plate2.GetSuffix())
    {
        int suffixCmp = strcmp(plate1.GetSuffix(), plate2.GetSuffix());
        return suffixCmp < 0 ? plate1 : plate2;
    }
    else if (plate1.GetSuffix())
    {
        return plate2;
    }
    else if (plate2.GetSuffix())
    {
        return plate1;
    }

    return plate1; // They're equal
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

const char* registration_plate::to_string() const {
    // Calculate required buffer size
    size_t size = 10; // Max would be 2 (prefix) + 4 (number) + 2 (suffix) + 1 (null terminator)
    static char* buffer = new char[size];
    
    // Clear buffer
    memset(buffer, 0, size);
    
    // Build string
    if (prefix)
        strcat(buffer, prefix);
    
    char numStr[5];
    sprintf(numStr, "%d", number);
    strcat(buffer, numStr);
    
    if (suffix)
        strcat(buffer, suffix);
    
    return buffer;
}
