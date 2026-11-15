#include "domain/screening.h"

#include <gtest/gtest.h>

using namespace MovieBooking;

TEST(ScreeningTests, ConstructorInitializesProperties)
{
    Movie movie(1, "Star Wars: A New Hope");
    Theater theater(1, "Le Grand Rex");

    const auto startTime = std::chrono::system_clock::now();

    Screening screening(100, movie, theater, startTime);

    EXPECT_EQ(screening.GetId(), 100);
    EXPECT_EQ(screening.GetMovie().GetId(), 1);
    EXPECT_EQ(screening.GetTheater().GetId(), 1);
    EXPECT_EQ(screening.GetStartTime(), startTime);
}