#include "Contracts/ucn.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <cstdio>    // for sprintf_s and sscanf_s
#include <cstdlib>   // for std::strtol
#include <algorithm> // for std::find

ucn::ucn() = default;

ucn::ucn(const char *input_ucn)
    : year(), month(), day(), region(), uniqueDigit()
{
    if (!input_ucn) {
        throw std::invalid_argument("UCN cannot be null");
    }
    
    if (input_ucn[0] == '\0') {
        throw std::invalid_argument("UCN cannot be empty");
    }

    if (!is_valid_ucn(input_ucn))
        throw std::invalid_argument("invalid UCN format");

    int year_val, month_val, day_val, region_val, unique_digit_val;
    if (sscanf_s(input_ucn, "%2d%2d%2d%3d%1d", &year_val, &month_val, &day_val, &region_val, &unique_digit_val) == 5)
    {
        // Process month and year logic
        if (month_val <= 12)
        {
            SetYear(1900 + year_val);
            SetMonth(month_val);
        }
        else if(month_val <= 52)
        {
            SetYear(2000 + year_val);
            SetMonth(month_val - 40);
        }
        else 
            throw std::invalid_argument("Invalid month value in UCN");
        SetDay(day_val);
        uniqueDigit = unique_digit_val;
        char region_str[4];
        sprintf_s(region_str, sizeof(region_str), "%03d", region_val);
        std::string region_name = RegionCalculator(region_str);
        SetRegion(region_name);
    }
    else
        throw std::invalid_argument("Failed to parse UCN");
}

int ucn::GetYear() const
{
    return year;
}
int ucn::GetMonth() const
{
    return month;
}
int ucn::GetDay() const
{
    return day;
}
std::string ucn::GetRegion() const
{
    return region;
}

void ucn::SetYear(int value)
{
    if (value < 1900 || value > 2100)
        throw std::out_of_range("Year must be between 1900 and 2100");
    year = value;
}
void ucn::SetMonth(int value)
{
    if (value < 1 || value > 12)
        throw std::out_of_range("Month must be between 1 and 12");
    month = value;
}
void ucn::SetDay(int value)
{
    if (value < 1 || value > 31)
        throw std::out_of_range("Day must be between 1 and 31");
    day = value;
}
void ucn::SetRegion(std::string value)
{
    region = value;
}

const std::string ucn::RegionCalculator(char *num)
{
    num_region = std::string(num);
    int firstNum = 0, SecondNum = 0, thirdNum = 0, result = 0;
    sscanf_s(num, "%1d%1d%1d", &firstNum, &SecondNum, &thirdNum);

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
    sscanf_s(num, "%1d%1d", &firstNum, &SecondNum);
    if (firstNum == 0)
    {
        return SecondNum;
    }
    else
    {
        return firstNum * 10 + SecondNum;
    }
}

std::ostream &operator<<(std::ostream &os, const ucn &egn)
{
    os << egn.to_string();
    return os;
}
std::istream &operator>>(std::istream &is, ucn &egn)
{
    char input[11]; // 10 digits + null terminator
    if (is >> input)
    {
        try
        {
            ucn temp(input);
            egn = temp;
        }
        catch (const std::exception &e)
        {
            // Mark stream as failed if parsing fails
            is.setstate(std::ios::failbit);
            std::cerr << "Error: " << e.what() << '\n';
            return is; // Return the stream in a failed state
        }
    }
    return is;
}

const std::string ucn::to_string() const
{
    std::string result;
    if (year < 10)
    {
        result += "0" + std::to_string(year);
    }
    else
    {
        result += std::to_string(year % 100);
    }

    if (month < 10)
    {
        result += "0" + std::to_string(month);
    }
    else
    {
        result += std::to_string(month);
    }
    if (day < 10)
    {
        result += "0" + std::to_string(day);
    }
    else
    {
        result += std::to_string(day);
    }
    result += num_region;
    result += std::to_string(uniqueDigit);
    return result;
}

bool ucn::operator<(const ucn &other) const
{
    if (year != other.year)
        return !(year < other.year);

    if (month != other.month)
        return !(month < other.month);

    if (day != other.day)
        return !(day < other.day);

    if (region.compare(other.region) < 0)
        return true;

    return false; // Equal
}

bool ucn::operator==(const ucn &other) const
{
    return year == other.year &&
           month == other.month &&
           day == other.day &&
           region == other.region;
}

bool ucn::is_valid_ucn(const char *egn)
{
    // Check if the UCN (Unified Civil Number) is valid
    // Implementation of the Bulgarian UCN validation algorithm
    if (!egn || strlen(egn) != 10)
        return false;

    // Check if all characters are digits
    for (int i = 0; i < 10; i++)
    {
        if (egn[i] < '0' || egn[i] > '9')
            return false;
    }

    // Weights for each position
    const int weights[9] = {2, 4, 8, 5, 10, 9, 7, 3, 6};
    int sum = 0;

    // Calculate the weighted sum of the first 9 digits
    for (int i = 0; i < 9; i++)
    {
        sum += (egn[i] - '0') * weights[i];
    }

    // Calculate the remainder when divided by 11
    int remainder = sum % 11;

    // If remainder is 10, it should be treated as 0
    if (remainder == 10)
        remainder = 0;

    // Check if the calculated control digit matches the actual 10th digit
    return (remainder == (egn[9] - '0'));
}