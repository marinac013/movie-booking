#pragma once

#include "services/booking_service.h"

namespace MovieBooking
{

class BookingController
{
public:
    static void RegisterRoutes(BookingService& bookingService);
};

}