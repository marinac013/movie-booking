#include "repos/booking_repo.h"

namespace MovieBooking
{

bool BookingRepository::Add(const Booking& booking)
{
    const auto result = this->bookings.emplace(booking.GetId(), booking);

    return result.second;
}

std::optional<Booking> BookingRepository::FindById(uint id) const
{
    const auto it = this->bookings.find(id);

    if (it == this->bookings.end())
    {
        return std::nullopt;
    }

    return it->second;
}

std::vector<Booking> BookingRepository::GetAll() const
{
    std::vector<Booking> bookings;

    bookings.reserve(this->bookings.size());

    for (const auto& entry : this->bookings)
    {
        bookings.push_back(entry.second);
    }

    return bookings;
}

bool BookingRepository::Exists(uint id) const
{
    return this->bookings.find(id) != this->bookings.end();
}

}