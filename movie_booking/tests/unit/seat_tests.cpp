#include "domain/seat.h"

#include <gtest/gtest.h>

using namespace MovieBooking;

TEST(SeatTests, ConstructorInitializesId)
{
    Seat seat("A1");

    EXPECT_EQ(seat.GetId(), "A1");
}
