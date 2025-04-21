#pragma once

/// A class which represents EGN (Edinen grazhdanski nomer)
class isp
{
private:
    int year = 0;
    int month = 0;
    int day = 0;
    // std::string region = "";
    char *region;

    isp(const char *);   // ctor
    ~isp();              // dtor
    isp(const isp &egn); // cpyctor
    isp &operator=(const isp &egn);

public:
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    void SetYear(int year);
    void SetMonth(int month);
    void SetDay(int day);

    // std::string Getregion();
    // std::string SetRegion();

    static bool is_valid_ucn(const char* egn);

    friend std::ostream &operator<<(std::ostream &os, const isp &egn);
    friend std::istream &operator>>(std::istream &is, const isp &egn);
};