#include "menu.h"

#include <iostream>
#include <string>
#include <vector>
#include <charconv>
#include <unordered_set>

namespace MovieBooking
{

namespace
{

bool ParseInteger(const std::string& input, int& value)
{
    const auto [ptr, error] =
        std::from_chars(input.data(), input.data() + input.size(), value);

    return error == std::errc() && ptr == input.data() + input.size();
}

bool CheckApiResponse(
    const ApiResponse& response,
    int expectedStatus,
    const std::string& statusError)
{
    if (!response.transportSuccess)
    {
        std::cout << "Failed to communicate with backend.\n";
        std::cout << response.error << "\n";
        return false;
    }

    if (response.statusCode != expectedStatus)
    {
        std::cout << statusError << " HTTP "
                  << response.statusCode << ".\n";
        std::cout << response.rawBody << "\n";
        return false;
    }

    if (!response.error.empty())
    {
        std::cout << response.error << "\n";
        return false;
    }

    return true;
}

}

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
    std::cout << "          MOVIE BOOKING SYSTEM      \n";
    std::cout << "====================================\n";
    std::cout << "1. Browse movies and book tickets\n";
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

    int value = 0;
    if (!ParseInteger(input, value))
    {
        return MenuOption::Invalid;
    }

    switch (value)
    {
        case 0:
            return MenuOption::Exit;

        case 1:
            return MenuOption::BrowseMoviesAndBookTickets;

        default:
            return MenuOption::Invalid;
    }
}

void Menu::HandleOption(MenuOption option)
{
    switch (option)
    {
        case MenuOption::BrowseMoviesAndBookTickets:
            this->BrowseMovies();
            break;

        case MenuOption::Invalid:
        default:
            std::cout << "\nInvalid option. Please try again.\n";
            break;
    }
}

bool Menu::ReadInteger(const std::string& prompt, int& value) const
{
    std::cout << prompt;

    std::string input;
    if (!std::getline(std::cin, input))
    {
        return false;
    }

    if (!ParseInteger(input, value))
    {
        std::cout << "Invalid input.\n";
        return false;
    }

    return true;
}

void Menu::BrowseMovies()
{
    std::cout << "\n========== AVAILABLE MOVIES ==========\n";

    const ApiResponse response = this->apiClient.Get("/api/movies");

    if (!CheckApiResponse(response, 200, "Backend returned"))
    {
        return;
    }

    std::vector<int> movieIds;
    std::vector<std::string> movieTitles;

    /// Extract movie IDs and titles.
    for (const Json::Value& movie : response.body)
    {
        movieIds.push_back(movie["id"].asInt());
        movieTitles.push_back(movie["title"].asString());
    }

    if (movieIds.empty())
    {
        std::cout << "No movies are currently available.\n";
        return;
    }

    //// Display available movies.
    for (std::size_t i = 0; i < movieIds.size(); ++i)
    {
        std::cout << i + 1 << ". "
                  << movieTitles[i]
                  << " (ID: " << movieIds[i] << ")\n";
    }

    /// Read movie selection.
    int selection = 0;

    if (!this->ReadInteger("\nSelect movie (0 to cancel): ", selection))
    {
        return;
    }

    if (selection == 0)
    {
        return;
    }

    if (selection < 1 ||
        static_cast<std::size_t>(selection) > movieIds.size())
    {
        std::cout << "Invalid movie selection.\n";
        return;
    }

    const int selectedMovieId = movieIds[selection - 1];

    std::cout << "\nSelected movie: "
              << movieTitles[selection - 1] << "\n";

    std::cout << "Movie ID: "
              << selectedMovieId << "\n";

    //// Continue with theater selection.
    this->BrowseTheaters(selectedMovieId);
}

void Menu::BrowseTheaters(int movieId)
{
    std::cout << "\n========== AVAILABLE THEATERS ==========\n";

    const std::string endpoint =
        "/api/movies/" + std::to_string(movieId) + "/theaters";

    const ApiResponse response = this->apiClient.Get(endpoint);

    if (!CheckApiResponse(response, 200, "Backend returned"))
    {
        return;
    }

    std::vector<int> theaterIds;
    std::vector<std::string> theaterNames;

    for (const Json::Value& theater : response.body)
    {
        theaterIds.push_back(theater["id"].asInt());
        theaterNames.push_back(theater["name"].asString());
    }

    if (theaterIds.empty())
    {
        std::cout << "No theaters are showing this movie.\n";
        return;
    }

    for (std::size_t i = 0; i < theaterNames.size(); ++i)
    {
        std::cout << i + 1 << ". " << theaterNames[i] << "\n";
    }

    int selection = 0;

    if (!this->ReadInteger("\nSelect theater (0 to cancel): ", selection))
    {
        return;
    }

    if (selection == 0)
    {
        return;
    }

    if (selection < 1 ||
        static_cast<std::size_t>(selection) > theaterIds.size())
    {
        std::cout << "Invalid theater selection.\n";
        return;
    }

    const int selectedTheaterId = theaterIds[selection - 1];

    std::cout << "\nSelected theater: "
              << theaterNames[selection - 1] << "\n";

    std::cout << "Theater ID: " << selectedTheaterId << "\n";

    this->BrowseScreenings(movieId, selectedTheaterId);
}

void Menu::BrowseScreenings(int movieId, int theaterId)
{
    std::cout << "\n========== AVAILABLE SCREENINGS ==========\n";

    const std::string endpoint =
        "/api/theaters/" + std::to_string(theaterId) + "/screenings";

    const ApiResponse response = this->apiClient.Get(endpoint);

    if (!CheckApiResponse(response, 200, "Backend returned"))
    {
        return;
    }

    std::vector<int> screeningIds;
    std::vector<std::string> screeningStartTimes;

    for (const Json::Value& screening : response.body)
    {
        if (screening["movieId"].asInt() != movieId)
        {
            continue;
        }

        screeningIds.push_back(screening["id"].asInt());
        screeningStartTimes.push_back(screening["startTime"].asString());
    }

    if (screeningIds.empty())
    {
        std::cout << "No screenings available for this movie "
                     "at the selected theater.\n";
        return;
    }

    for (std::size_t i = 0; i < screeningIds.size(); ++i)
    {
        std::cout << i + 1 << ". "
                  << screeningStartTimes[i]
                  << " (Screening ID: " << screeningIds[i] << ")\n";
    }

    int selection = 0;

    if (!this->ReadInteger("\nSelect screening (0 to cancel): ", selection))
    {
        return;
    }

    if (selection == 0)
    {
        return;
    }

    if (selection < 1 ||
        static_cast<std::size_t>(selection) > screeningIds.size())
    {
        std::cout << "Invalid screening selection.\n";
        return;
    }

    const int selectedScreeningId = screeningIds[selection - 1];

    std::cout << "\nSelected screening: "
              << screeningStartTimes[selection - 1] << "\n";

    std::cout << "Screening ID: "
              << selectedScreeningId << "\n";

    this->BrowseSeats(selectedScreeningId);}

void Menu::BrowseSeats(int screeningId)
{
    std::cout << "\n========== AVAILABLE SEATS ==========\n";

    const std::string endpoint =
        "/api/screenings/" + std::to_string(screeningId) + "/seats";

    const ApiResponse response = this->apiClient.Get(endpoint);

    if (!CheckApiResponse(response, 200, "Backend returned"))
    {
        return;
    }

    std::vector<std::string> availableSeats;

    for (const Json::Value& seat : response.body)
    {
        availableSeats.push_back(seat.asString());
    }

    if (availableSeats.empty())
    {
        std::cout << "No available seats for this screening.\n";
        return;
    }

    /// Display available seats.
    std::cout << "Available seats:\n\n";

    for (std::size_t i = 0; i < availableSeats.size(); ++i)
    {
        std::cout << std::left
                  << std::setw(6)
                  << availableSeats[i];

        if ((i + 1) % 5 == 0 || i + 1 == availableSeats.size())
        {
            std::cout << "\n";
        }
    }

    /// Read seat selection.
    std::cout << "\nEnter seat IDs separated by commas (e.g. A1,A2): ";

    std::string input;

    if (!std::getline(std::cin, input))
    {
        return;
    }

    /// Parse selected seats.
    std::vector<std::string> selectedSeats;
    std::unordered_set<std::string> uniqueSeats;

    std::stringstream inputStream(input);
    std::string seatId;

    while (std::getline(inputStream, seatId, ','))
    {
        const std::size_t first = seatId.find_first_not_of(" \t");
        const std::size_t last = seatId.find_last_not_of(" \t");

        if (first == std::string::npos)
        {
            std::cout << "Invalid seat selection.\n";
            return;
        }

        seatId = seatId.substr(first, last - first + 1);

        if (!uniqueSeats.insert(seatId).second)
        {
            std::cout << "Duplicate seat selected: "
                      << seatId << "\n";
            return;
        }

        if (std::find(
                availableSeats.begin(),
                availableSeats.end(),
                seatId) == availableSeats.end())
        {
            std::cout << "Seat is not available: "
                      << seatId << "\n";
            return;
        }

        selectedSeats.push_back(seatId);
    }

    if (selectedSeats.empty())
    {
        std::cout << "No seats selected.\n";
        return;
    }

    /// Display booking summary.
    std::cout << "\n========== BOOKING SUMMARY ==========\n";
    std::cout << "Screening ID: " << screeningId << "\n";
    std::cout << "Selected seats: ";

    for (std::size_t i = 0; i < selectedSeats.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << ", ";
        }

        std::cout << selectedSeats[i];
    }

    std::cout << "\nNumber of tickets: "
              << selectedSeats.size() << "\n";

    /// Ask for confirmation.
    std::cout << "\nConfirm booking? (y/n): ";

    std::string confirmation;

    if (!std::getline(std::cin, confirmation))
    {
        return;
    }

    if (confirmation != "y" && confirmation != "Y")
    {
        std::cout << "Booking cancelled.\n";
        return;
    }

    /// Create booking request.
    Json::Value requestBody;
    requestBody["seats"] = Json::arrayValue;

    for (const std::string& selectedSeat : selectedSeats)
    {
        requestBody["seats"].append(selectedSeat);
    }

    const std::string bookingEndpoint =
        "/api/screenings/" + std::to_string(screeningId) + "/bookings";

    const ApiResponse bookingResponse =
        this->apiClient.Post(bookingEndpoint, requestBody);

    if (!CheckApiResponse(bookingResponse, 201, "\nBooking failed."))
    {
        return;
    }

    /// Display booking confirmation.
    std::cout << "\n========== BOOKING CONFIRMED ==========\n";

    const Json::Value& bookingId = bookingResponse.body["bookingId"];

    std::cout << "Booking ID: " << bookingId.asInt() << "\n";
    std::cout << "Screening ID: " << screeningId << "\n";
    std::cout << "Seats: ";

    for (std::size_t i = 0; i < selectedSeats.size(); ++i)
    {
        if (i > 0)
        {
            std::cout << ", ";
        }

        std::cout << selectedSeats[i];
    }

    std::cout << "\nTickets booked: "
              << selectedSeats.size() << "\n";

    std::cout << "=======================================\n";
}

}