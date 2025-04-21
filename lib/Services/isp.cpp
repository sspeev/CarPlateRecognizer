#include "../Contracts/isp.hpp"
#include <cstring>
#include <stdexcept>
#include <iostream>

isp::isp(const char *input_isp) // constructor
    : year(0), month(0), day(0), region()
{
    try
    {
        if (input_isp && input_isp[0])
        {
            char *year = new char[2];
            char *month = new char[2];
            char *day = new char[2];
            char *region_number = new char[3];
            sscanf(input_isp, "%2d%2d%2d%3d", year, month, day, region_number);
            int year_INT = NumberFixer(year);
            int month_INT = NumberFixer(month);
            int day_INT = NumberFixer(day);
            if (month_INT <= 12)
            {
                SetYear(1900 + year_INT);
                SetMonth(month_INT);
            }
            else
            {
                SetYear(2000 + year_INT);
                SetMonth(month_INT - 40);
            }
            SetDay(day_INT);
            std::string region_STR = RegionCalculator(region_number);
            SetRegion(region_STR);
            delete[] year;
            delete[] month;
            delete[] day;
            delete[] region_number;
        }
        else
            throw std::invalid_argument("invalid input");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int isp::GetYear() const
{
    return year;
}

int isp::GetMonth() const
{
    return month;
}

int isp::GetDay() const
{
    return day;
}
std::string isp::GetRegion() const
{
    return region;
}

void isp::SetYear(int value)
{
    year = value;
}

void isp::SetMonth(int value)
{
    month = value;
}

void isp::SetDay(int value)
{
    day = value;
}

void isp::SetRegion(std::string value)
{
    region = value;
}

const std::string isp::RegionCalculator(char *num)
{
    int firstNum = 0, SecondNum = 0, thirdNum = 0, result = 0;
    sscanf(num, "%1d%1d%1d", &firstNum, &SecondNum, &thirdNum);

    if (firstNum == 0)
    {
        if (SecondNum == 0)
        {
            result = thirdNum;
        }
        else
            result = SecondNum * 10 + thirdNum;
    }
    else
        result = firstNum * 100 + SecondNum * 10 + thirdNum;

    if (result >= 0 && result <= 43)
        return "Blagoevgrad";
    if (result >= 44 && result <= 93)
        return "Burgas";
    if (result >= 94 && result <= 139)
        return "Varna";
    if (result >= 140 && result <= 169)
        return "Veliko Tarnovo";
    if (result >= 170 && result <= 183)
        return "Vidin";
    if (result >= 184 && result <= 217)
        return "Vratsa";
    if (result >= 218 && result <= 233)
        return "Gabrovo";
    if (result >= 234 && result <= 281)
        return "Kardzhali";
    if (result >= 282 && result <= 301)
        return "Kyustendil";
    if (result >= 302 && result <= 319)
        return "Lovech";
    if (result >= 320 && result <= 341)
        return "Montana";
    if (result >= 342 && result <= 377)
        return "Pazardzhik";
    if (result >= 378 && result <= 395)
        return "Pernik";
    if (result >= 396 && result <= 435)
        return "Pleven";
    if (result >= 436 && result <= 501)
        return "Plovdiv";
    if (result >= 502 && result <= 527)
        return "Razgrad";
    if (result >= 528 && result <= 555)
        return "Ruse";
    if (result >= 556 && result <= 575)
        return "Silistra";
    if (result >= 576 && result <= 601)
        return "Sliven";
    if (result >= 602 && result <= 623)
        return "Smolyan";
    if (result >= 624 && result <= 721)
        return "Sofia-grad";
    if (result >= 722 && result <= 751)
        return "Sofia-okrag";
    if (result >= 752 && result <= 789)
        return "Stara Zagora";
    if (result >= 790 && result <= 821)
        return "Dobrich";
    if (result >= 822 && result <= 843)
        return "Targovishte";
    if (result >= 844 && result <= 871)
        return "Haskovo";
    if (result >= 872 && result <= 903)
        return "Shumen";
    if (result >= 904 && result <= 925)
        return "Yambol";
    if (result >= 926 && result <= 999)
        return "Other/Unknown";

    return "Invalid region";
}

const int NumberFixer(char *num)

{
    int firstNum = 0, SecondNum = 0;
    sscanf(num, "%1d%1d", firstNum, SecondNum);
    if (firstNum == 0)
    {
        return SecondNum;
    }
    else
    {
        return firstNum * 10 + SecondNum;
    }
}

static bool is_valid_isp(const char *egn)
{
    // nqma da se zanimavam da implementiram toq tup algorithum
}

std::ostream &operator<<(std::ostream &os, const isp &egn)
{
    if (egn.day)
        os << egn.day;
    if(egn.month)
        os << egn.month;
    if(egn.year)
        os << egn.year;
    return os;
}

std::istream& operator>>(std::istream& is, isp& egn)
{
    char input[11]; // 10 digits + null terminator
    if (is >> input) {
        try {
            isp temp(input);
            egn = temp;
        }
        catch (const std::exception& e) {
            // Mark stream as failed if parsing fails
            is.setstate(std::ios::failbit);
        }
    }
    return is;
}

const char* isp::to_string()
{
    // Use a static buffer for the result
    static char buffer[11]; // Large enough for year + month + day + null terminator
    snprintf(buffer, sizeof(buffer), "%02d%02d%02d", year, month, day);
    return buffer;
}