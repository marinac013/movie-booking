#include <chrono>
#include <string>
#include <vector>

namespace MovieBooking
{

/** @brief Represents a movie booking. */
class Booking
{
public:
    /**
     * @brief Constructs a booking.
     * @param id Unique booking ID.
     * @param screeningId Screening ID.
     * @param seatIds Reserved seat IDs.
     * @param bookedAt Booking timestamp.
     */
    Booking(
        uint id,
        uint screeningId,
        const std::vector<std::string>& seatIds,
        std::chrono::system_clock::time_point bookedAt);

    /**
     * @brief Returns the booking ID.
     * @return The booking ID.
     */
    uint GetId() const;

    /**
     * @brief Returns the screening ID.
     * @return The screening ID.
     */
    uint GetScreeningId() const;

    /**
     * @brief Returns the reserved seat IDs.
     * @return A vector containing the seat IDs.
     */
    std::vector<std::string> GetSeatIds() const;

    /**
     * @brief Returns the booking timestamp.
     * @return The booking timestamp.
     */
    std::chrono::system_clock::time_point GetBookedAt() const;

private:
    /** @brief The booking ID. */
    uint id;
    /** @brief The screening ID. */
    uint screeningId;
    /** @brief The reserved seat IDs. */
    std::vector<std::string> seatIds;
    /** @brief The booking timestamp. */
    std::chrono::system_clock::time_point bookedAt;
};

}