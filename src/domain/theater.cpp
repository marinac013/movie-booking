#include "domain/theater.h"

#include <stdexcept>

namespace MovieBooking
{

Theater::Theater(uint id, const std::string& name)
    : id(id)
    , name(name)
{
    if (name.empty())
    {
        throw std::invalid_argument("[ ERROR ] Theater name cannot be empty.");
    }
}

uint Theater::GetId() const
{
    return id;
}

const std::string& Theater::GetName() const
{
    return name;
}

uint Theater::GetCapacity() const
{
    return SEAT_CAPACITY;
}

}