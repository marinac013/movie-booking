#pragma once

namespace MovieBooking
{

class Menu
{
public:
    void Run();

private:
    enum class MenuOption
    {
        Exit = 0,
        BrowseMovies = 1,
        FindTheaters = 2,
        ViewScreenings = 3,
        ViewAvailableSeats = 4,
        BookTickets = 5,
        ViewBookingDetails = 6,
        Invalid = -1
    };

    void DisplayMenu() const;
    MenuOption ReadOption() const;
    void HandleOption(MenuOption option);
};

}