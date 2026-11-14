#include "domain/seat.h"

#include <stdexcept>

namespace MovieBooking
{

Seat::Seat(const std::string& id)
    : id(id)
{
    if (id.empty())
    {
        throw std::invalid_argument("[ ERROR ]Seat ID can't be empty.");
    }
}

const std::string& Seat::GetId() const
{
    return id;
}

}