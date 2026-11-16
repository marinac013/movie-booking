#pragma once

#include "api_client.h"
#include <iomanip>

namespace MovieBooking
{

/** @brief A class representing the main menu for the movie booking application. */
class Menu
{
public:
    /** @brief Constructs a new menu instance. */
    Menu(ApiClient& apiClient) : apiClient(apiClient) {}
    /** @brief Runs the main menu loop. */
    void Run();

private:
    /** @brief Represents the available menu options. */
    enum class MenuOption
    {
        Exit = 0,
        BrowseMoviesAndBookTickets = 1,
        Invalid = -1
    };
    /** @brief Displays the main menu options. */
    void DisplayMenu() const;
    /** @brief Reads the user's menu option selection. */
    MenuOption ReadOption() const;
    /** 
    * @brief Handles the selected menu option.
    * @param option The selected menu option. 
    */
    void HandleOption(MenuOption option);
    /** @brief Reads an integer from the user. 
    * @param prompt The prompt to display.
    * @param value The parsed integer value.
    * @return True if parsing was successful, false otherwise.
    */
    bool ReadInteger(const std::string& prompt, int& value) const;
    /** @brief Browses available movies. */
    void BrowseMovies();
    /** @brief Browses theaters for a given movie. 
    * @param movieId The ID of the selected movie.
    */
    void BrowseTheaters(int movieId);
    /** @brief Browses screenings for a given movie and theater. 
     * @param movieId The ID of the selected movie.
     * @param theaterId The ID of the selected theater.
     */
    void BrowseScreenings(int movieId, int theaterId);
    /** @brief Browses seats for a given screening. 
     * @param screeningId The ID of the selected screening.
     */
    void BrowseSeats(int screeningId);

    /** @brief The API client for communicating with the backend. */
    ApiClient& apiClient;
};

}