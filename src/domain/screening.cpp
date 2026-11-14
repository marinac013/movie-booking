#include "domain/screening.h"

#include <stdexcept>

namespace MovieBooking
{

Screening::Screening(
    uint id,
    const Movie& movie,
    const Theater& theater,
    const std::chrono::system_clock::time_point& startTime)
    : id(id)
    , movie(movie)
    , theater(theater)
    , startTime(startTime)
{
}

uint Screening::GetId() const
{
    return id;
}

const Movie& Screening::GetMovie() const
{
    return movie;
}

const Theater& Screening::GetTheater() const
{
    return theater;
}

std::chrono::system_clock::time_point Screening::GetStartTime() const
{
    return startTime;
}

std::vector<std::string> Screening::GetAvailableSeats() const
{
    std::vector<std::string> availableSeats;

    for (uint i = 1; i <= Theater::SEAT_CAPACITY; ++i)
    {
        const std::string seatId = "A" + std::to_string(i);

        if (this->bookedSeatIds.find(seatId) == this->bookedSeatIds.end())
        {
            availableSeats.push_back(seatId);
        }
    }

    return availableSeats;
}

bool Screening::IsValidSeatId(const std::string& seatId) const
{
    if (seatId.size() < 2 || seatId[0] != 'A')
    {
        return false;
    }

    try
    {
        const uint seatNumber = std::stoi(seatId.substr(1));

        return seatId == "A" + std::to_string(seatNumber)
            && seatNumber >= 1
            && seatNumber <= Theater::SEAT_CAPACITY;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

bool Screening::IsSeatAvailable(const std::string& seatId) const
{
    if (!this->IsValidSeatId(seatId))
    {
        return false;
    }

    return this->bookedSeatIds.find(seatId) == this->bookedSeatIds.end();
}

bool Screening::ReserveSeats(const std::vector<std::string>& seatIds)
{
    if (seatIds.empty())
    {
        return false;
    }

    std::unordered_set<std::string> requestedSeats;

    // Validate every requested seat before modifying the inventory.
    for (const auto& seatId : seatIds)
    {
        if (!this->IsSeatAvailable(seatId))
        {
            return false;
        }

        if (!requestedSeats.insert(seatId).second)
        {
            return false;
        }
    }

    // All seats are available. Reserve them.
    for (const auto& seatId : seatIds)
    {
        this->bookedSeatIds.insert(seatId);
    }

    return true;
}

}