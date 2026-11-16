#pragma once

#include "api_client.h"
#include <iomanip>

namespace MovieBooking
{

class Menu
{
public:
    Menu(ApiClient& apiClient) : apiClient(apiClient) {}

    void Run();

private:
    enum class MenuOption
    {
        Exit = 0,
        BrowseMoviesAndBookTickets = 1,
        Invalid = -1
    };
    
    void DisplayMenu() const;
    MenuOption ReadOption() const;
    void HandleOption(MenuOption option);

    bool ReadInteger(const std::string& prompt, int& value) const;
    void BrowseMovies();
    void BrowseTheaters(int movieId);
    void BrowseScreenings(int movieId, int theaterId);
    void BrowseSeats(int screeningId);

    ApiClient& apiClient;
};

}