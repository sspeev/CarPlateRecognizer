#pragma once
#include <iostream>
#include <string>

class isp
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
    isp();
    isp(const char * input); // ctor
    // ~isp();              // dtor
    // isp(const isp &egn); // cpyctor
    // isp &operator=(const isp &egn);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    std::string GetRegion() const;

    void SetYear(int year);
    void SetMonth(int month);
    void SetDay(int day);
    void SetRegion(std::string region);

    // static bool is_valid_ucn(const char *egn);
    const std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &os, const isp &egn);
    friend std::istream &operator>>(std::istream &is, isp &egn);
    bool operator<(const isp &other) const;
    bool operator==(const isp &other) const;
};