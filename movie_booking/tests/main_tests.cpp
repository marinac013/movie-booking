#include "app_info.h"

#include <gtest/gtest.h>

TEST(AppInfoTests, ApplicationNameIsCorrect)
{
    const std::string applicationName =
        MovieBooking::GetApplicationName();

    EXPECT_EQ(applicationName, "Movie Booking Backend");
}