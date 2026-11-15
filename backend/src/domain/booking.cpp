#include "domain/booking.h"

#include <stdexcept>

namespace MovieBooking
{

Booking::Booking(
    uint id,
    uint screeningId,
    const std::vector<std::string>& seatIds,
    std::chrono::system_clock::time_point bookedAt)
    : id(id),
      screeningId(screeningId),
      seatIds(seatIds),
      bookedAt(bookedAt)
{
    if (seatIds.empty())
    {
        throw std::invalid_argument("[ ERROR ] A booking must contain at least one seat.");
    }
}

uint Booking::GetId() const
{
    return this->id;
}

uint Booking::GetScreeningId() const
{
    return this->screeningId;
}

std::vector<std::string> Booking::GetSeatIds() const
{
    return this->seatIds;
}

std::chrono::system_clock::time_point Booking::GetBookedAt() const
{
    return this->bookedAt;
}

}