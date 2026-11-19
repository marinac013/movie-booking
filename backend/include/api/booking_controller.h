#pragma once

#include "services/booking_service.h"

namespace MovieBooking
{

/** @brief Represents the booking controller. */
class BookingController
{
public:
    /**
     * @brief Registers the booking routes.
     * @param bookingService The booking service.
     */
    static void RegisterRoutes(BookingService& bookingService);
};

}