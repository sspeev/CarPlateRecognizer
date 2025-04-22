#pragma once

/// A class which represents EGN (Edinen grazhdanski nomer)
class isp
{
private:
    int year = 0;
    int month = 0;
    int day = 0;
    std::string region = "";

public:
    isp(const char *); // ctor
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
    const char *to_string();

    friend std::ostream &operator<<(std::ostream &os, const isp &egn);
    friend std::istream &operator>>(std::istream &is, isp &egn);
    bool operator<(const isp &other) const;
    bool operator==(const isp &other) const;

private:
    const std::string RegionCalculator(char *num);
    const int NumberFixer(char *num);
};