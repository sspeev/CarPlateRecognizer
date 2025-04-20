#include "../Contracts/isp.hpp"
#include <cstring>
#include <stdexcept>

isp::isp(const char *input_isp) // constructor
    : year(0), month(0), day(0)
{
    if (input_isp && input_isp[0])
    {
        sscanf(input_isp, "%2d%2d%2d", year, month, day);

        if (month <= 12)
        {
            SetYear(1900 + year);
            SetMonth(month);
        }
        else{
            SetYear(2000 + year);
            SetMonth(month - 40);
        }
        SetDay(day);
    }
    else
        throw std::invalid_argument("invalid input");
}