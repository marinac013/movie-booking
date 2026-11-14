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

}