#include <iostream>
#include "Contracts/isp.hpp"
#include "Contracts/registration_plate.hpp"
#include "Contracts/vehicle_register.hpp"

int main()
{
    char *plate2 = "CB3408KK";
    char *plate3 = "CB2858MK";
    char *egn1 = "0549050484";
    char *egn2 = "0552012940";

    registration_plate plate(plate2);
    registration_plate plate1(plate3);

    isp owner(egn1);
    isp owner1(egn2);

    vehicle_register reg;
    reg.Register(plate, owner);
    reg.Register(plate1, owner1);

    std::cout << "Registered vehicles:\n"
              << reg << std::endl;

    return 0;
}