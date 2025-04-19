#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "Contracts/registration_plate.hpp"

class registration_plate
{
private:
    std::string prefix = "";
    int number = 0;
    std::string suffix = "";

public:
    // Prefix getters and setters
    void SetPrefix(const std::string &input);
    std::string GetPrefix() const;

    // Number getters and setters
    void SetNumber(int input);
    int GetNumber() const;

    // Suffix getters and setters
    void SetSuffix(const std::string &input);
    std::string GetSuffix() const;
};

// Implement the methods declared in the header
void registration_plate::SetPrefix(const std::string &input)
{
    if (input.length() > 2)
    {
        throw std::invalid_argument("Prefix must be between 0 and 2 long");
    }
    prefix = input;
}

std::string registration_plate::GetPrefix() const
{
    return prefix;
}

void registration_plate::SetNumber(int input)
{
    // Remove the isdigit check - input is already an int
    if (input < 1000 || input > 9999) // Note the correction from && to ||
    {
        throw std::invalid_argument("Must be a number between 1000 and 9999");
    }
    number = input;
}

int registration_plate::GetNumber() const
{
    return number;
}

void registration_plate::SetSuffix(const std::string &input)
{
    if (input.length() > 2)
    {
        throw std::invalid_argument("Suffix must be between 0 and 2 long");
    }
    suffix = input;
}

std::string registration_plate::GetSuffix() const
{
    return suffix;
}