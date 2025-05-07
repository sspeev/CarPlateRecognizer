#ifndef REGISTRATION_PLATE_HPP
#define REGISTRATION_PLATE_HPP
#pragma once

#include <iostream>
#include <string>

class registration_plate
{
private:
    std::string prefix;
    int number;
    std::string suffix;

public:
    registration_plate();
    registration_plate(const char *plate = nullptr);

    void SetPrefix(const std::string &input);
    const std::string GetPrefix() const;

    void SetNumber(int n);
    int GetNumber() const;

    void SetSuffix(const std::string &s);
    const std::string GetSuffix() const;

    const std::string to_string() const;

    // Comparison operators
    friend bool operator==(const registration_plate &plate1, const registration_plate &plate2);
    friend bool operator<(const registration_plate &plate1, const registration_plate &plate2);

    friend std::ostream &operator<<(std::ostream &os, const registration_plate &plate);
    friend std::istream &operator>>(std::istream &is, registration_plate &plate);
};

#endif // REGISTRATION_PLATE_HPP