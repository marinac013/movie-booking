#pragma once

#include "repos/booking_repo.h"
#include "repos/screening_repo.h"

#include <optional>
#include <string>
#include <vector>
#include <atomic>

namespace MovieBooking
{

/** @brief Represents the status of a booking operation. */
enum class BookingStatus
{
    Success,
    ScreeningNotFound,
    EmptySeatSelection,
    InvalidSeat,
    DuplicateSeat,
    SeatUnavailable,
    PersistenceError
};

/** @brief Represents the result of a booking operation. */
struct BookingResult
{
    BookingStatus status;
    std::optional<Booking> booking;

    /** @brief Checks if the booking operation was successful.
     *  @return True if the operation was successful, otherwise false.
     */
    bool IsSuccess() const
    {
        return this->status == BookingStatus::Success;
    }
};

/** @brief Manages booking operations for screenings. */
class BookingService
{
public:
    /** @brief Constructs a new booking service instance.
     *  @param screeningRepository The screening repository instance.
     *  @param bookingRepository The booking repository instance.
     */
    BookingService(
        ScreeningRepository& screeningRepository,
        BookingRepository& bookingRepository);

    /**
     * @brief Books one or more seats for a screening.
     * @param screeningId Screening ID.
     * @param seatIds IDs of requested seats.
     * @return Booking result, including the booking on success.
     */
    BookingResult BookSeats(
        uint screeningId,
        const std::vector<std::string>& seatIds);

    /**
    * @brief Finds a booking by its ID.
    * @param bookingId Booking ID.
    * @return The booking if found; otherwise std::nullopt.
    */
    std::optional<Booking> GetBookingById(int bookingId) const;

private:
    /** @brief The screening repository instance. */
    ScreeningRepository& screeningRepository;
    /** @brief The booking repository instance. */
    BookingRepository& bookingRepository;
    /** @brief Atomic counter for generating unique booking IDs. */
    std::atomic<uint> nextBookingId{1};
};

}