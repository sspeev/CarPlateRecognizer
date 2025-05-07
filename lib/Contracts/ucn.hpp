#pragma once
#include <iostream>
#include <string>

class ucn
{
private:
    int year;
    int month;
    int day;
    std::string region;
    std::string num_region;

    const std::string RegionCalculator(char *num);
    const int NumberFixer(char *num);

public:
    ucn();
    ucn(const char *input);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    std::string GetRegion() const;

    void SetYear(int year);
    void SetMonth(int month);
    void SetDay(int day);
    void SetRegion(std::string region);

    static bool is_valid_ucn(const char *egn);
    const std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &os, const ucn &egn);
    friend std::istream &operator>>(std::istream &is, ucn &egn);
    bool operator<(const ucn &other) const;
    bool operator==(const ucn &other) const;
};