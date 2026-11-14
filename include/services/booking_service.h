#pragma once

#include "repos/booking_repo.h"
#include "repos/screening_repo.h"

#include <optional>
#include <string>
#include <vector>
#include <atomic>

namespace MovieBooking
{

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

struct BookingResult
{
    BookingStatus status;
    std::optional<Booking> booking;

    bool IsSuccess() const
    {
        return this->status == BookingStatus::Success;
    }
};

class BookingService
{
public:
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

private:
    ScreeningRepository& screeningRepository;
    BookingRepository& bookingRepository;

    std::atomic<uint> nextBookingId{1};
};

}