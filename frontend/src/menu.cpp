#include "menu.h"

#include <charconv>
#include <iostream>
#include <string>

namespace MovieBooking
{

void Menu::Run()
{
    bool running = true;

    while (running)
    {
        this->DisplayMenu();

        const MenuOption option = this->ReadOption();

        if (option == MenuOption::Exit)
        {
            running = false;
        }
        else
        {
            this->HandleOption(option);
        }

        if (running)
        {
            std::cout << "\nPress Enter to continue...";
            std::string input;
            std::getline(std::cin, input);
        }
    }

    std::cout << "\nExiting Movie Booking Frontend.\n";
}

void Menu::DisplayMenu() const
{
    std::cout << "\n";
    std::cout << "====================================\n";
    std::cout << "       MOVIE BOOKING SYSTEM         \n";
    std::cout << "====================================\n";
    std::cout << "1. Browse movies\n";
    std::cout << "2. Find theaters\n";
    std::cout << "3. View screenings\n";
    std::cout << "4. View available seats\n";
    std::cout << "5. Book tickets\n";
    std::cout << "6. View booking details\n";
    std::cout << "0. Exit\n";
    std::cout << "------------------------------------\n";
    std::cout << "Select option: ";
}

Menu::MenuOption Menu::ReadOption() const
{
    std::string input;

    if (!std::getline(std::cin, input))
    {
        return MenuOption::Exit;
    }

    if (input.empty())
    {
        return MenuOption::Invalid;
    }

    int value = -1;

    const char* begin = input.data();
    const char* end = begin + input.size();

    const auto result = std::from_chars(begin, end, value);

    if (result.ec != std::errc() || result.ptr != end)
    {
        return MenuOption::Invalid;
    }

    switch (value)
    {
        case 0:
            return MenuOption::Exit;

        case 1:
            return MenuOption::BrowseMovies;

        case 2:
            return MenuOption::FindTheaters;

        case 3:
            return MenuOption::ViewScreenings;

        case 4:
            return MenuOption::ViewAvailableSeats;

        case 5:
            return MenuOption::BookTickets;

        case 6:
            return MenuOption::ViewBookingDetails;

        default:
            return MenuOption::Invalid;
    }
}

void Menu::HandleOption(MenuOption option)
{
    switch (option)
    {
        case MenuOption::BrowseMovies:
            std::cout << "\nBrowse movies selected.\n";
            break;

        case MenuOption::FindTheaters:
            std::cout << "\nFind theaters selected.\n";
            break;

        case MenuOption::ViewScreenings:
            std::cout << "\nView screenings selected.\n";
            break;

        case MenuOption::ViewAvailableSeats:
            std::cout << "\nView available seats selected.\n";
            break;

        case MenuOption::BookTickets:
            std::cout << "\nBook tickets selected.\n";
            break;

        case MenuOption::ViewBookingDetails:
            std::cout << "\nView booking details selected.\n";
            break;

        case MenuOption::Invalid:
        default:
            std::cout << "\nInvalid option. Please try again.\n";
            break;
    }
}

}