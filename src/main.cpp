#include "app_info.h"

#include <iostream>

int main()
{
    std::cout << "======================================" << std::endl;
    std::cout << MovieBooking::GetApplicationName() << std::endl;
    std::cout << "======================================" << std::endl;

    std::cout << "Application started successfully!" << std::endl;

    return 0;
}