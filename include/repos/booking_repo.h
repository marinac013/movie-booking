#include "domain/booking.h"

#include <optional>
#include <unordered_map>
#include <vector>

namespace MovieBooking
{

class BookingRepository
{
public:
    /**
     * @brief Adds a booking.
     * @param booking Booking to add.
     * @return True if added; false if its ID already exists.
     */
    bool Add(const Booking& booking);

    /**
     * @brief Finds a booking by ID.
     * @param id Booking ID.
     * @return Booking if found; otherwise std::nullopt.
     */
    std::optional<Booking> FindById(uint id) const;

    /**
     * @brief Returns all stored bookings.
     */
    std::vector<Booking> GetAll() const;

    /**
     * @brief Checks whether a booking exists.
     */
    bool Exists(uint id) const;

private:
    std::unordered_map<uint, Booking> bookings;
};

}