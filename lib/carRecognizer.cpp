#include <iostream>
#include "Services/registration_plate.cpp"
int test()
{
    std::string prefix;
    std::cin >> prefix;
    try
    {
        registration_plate plate;
        plate.SetPrefix(prefix);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}