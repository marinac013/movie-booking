#include "domain/booking.h"

#include <gtest/gtest.h>

#include <chrono>

using namespace MovieBooking;

TEST(BookingTests, ConstructorInitializesProperties)
{
    Booking booking(1, 1, {"A1", "A2"}, std::chrono::system_clock::now());

    EXPECT_EQ(booking.GetId(), 1);
    EXPECT_EQ(booking.GetScreeningId(), 1);
    EXPECT_EQ(booking.GetSeatIds().size(), 2);
}