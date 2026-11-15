#include "services/booking_service.h"

#include <chrono>
#include <unordered_set>

namespace MovieBooking
{

BookingService::BookingService(
    ScreeningRepository& screeningRepository,
    BookingRepository& bookingRepository)
    : screeningRepository(screeningRepository),
      bookingRepository(bookingRepository)
{
}

BookingResult BookingService::BookSeats(
    uint screeningId,
    const std::vector<std::string>& seatIds)
{
    // Acquire exclusive access to this screening.
    auto screeningLock = this->screeningRepository.LockFor(screeningId);
    
    // Check whether the screening exists.
    auto screening = this->screeningRepository.FindById(screeningId);

    if (!screening.has_value())
    {
        return { BookingStatus::ScreeningNotFound, std::nullopt };
    }

    const Screening originalScreening = *screening;

    // At least one seat must be requested.
    if (seatIds.empty())
    {
        return { BookingStatus::EmptySeatSelection, std::nullopt };
    }

    std::unordered_set<std::string> requestedSeats;

    // Validate all requested seats before changing the inventory.
    for (const auto& seatId : seatIds)
    {
        if (!screening->IsValidSeatId(seatId))
        {
            return { BookingStatus::InvalidSeat, std::nullopt };
        }

        if (!requestedSeats.insert(seatId).second)
        {
            return { BookingStatus::DuplicateSeat, std::nullopt };
        }

        if (!screening->IsSeatAvailable(seatId))
        {
            return { BookingStatus::SeatUnavailable, std::nullopt };
        }
    }

    // Reserve all seats in the screening.
    if (!screening->ReserveSeats(seatIds))
    {
        return { BookingStatus::SeatUnavailable, std::nullopt };
    }

    // Create the booking.
    Booking booking(
        this->nextBookingId.fetch_add(1, std::memory_order_relaxed),
        screeningId,
        seatIds,
        std::chrono::system_clock::now());

    // Persist the updated screening before adding the booking record.
    if (!this->screeningRepository.Update(*screening))
    {
        return { BookingStatus::PersistenceError, std::nullopt };
    }

    if (!this->bookingRepository.Add(booking))
    {
        this->screeningRepository.Update(originalScreening);

        return { BookingStatus::PersistenceError, std::nullopt };
    }

    return { BookingStatus::Success, booking };
}

std::optional<Booking> BookingService::GetBookingById(
    int bookingId) const
{
    return this->bookingRepository.FindById(bookingId);
}

}