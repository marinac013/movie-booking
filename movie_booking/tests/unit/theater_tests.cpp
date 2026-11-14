#include "domain/theater.h"

#include <gtest/gtest.h>

using namespace MovieBooking;

TEST(TheaterTests, ConstructorInitializesProperties)
{
    Theater theater(5, "Le Grand Rex");

    EXPECT_EQ(theater.GetId(), 5);
    EXPECT_EQ(theater.GetName(), "Le Grand Rex");
}

TEST(TheaterTests, CapacityIsTwenty)
{
    Theater theater(5, "Le Grand Rex");

    EXPECT_EQ(theater.GetCapacity(), 20);
}