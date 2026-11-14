#include "domain/movie.h"

#include <gtest/gtest.h>

using namespace MovieBooking;

TEST(MovieTests, ConstructorInitializesProperties)
{
    Movie movie(17, "Star Wars: A New Hope");

    EXPECT_EQ(movie.GetId(), 17);
    EXPECT_EQ(movie.GetTitle(), "Star Wars: A New Hope");
}

TEST(MovieTests, RejectsEmptyTitle)
{
    EXPECT_THROW(Movie(1, ""), std::invalid_argument);
}

TEST(MovieTests, RejectsLongTitle)
{
    std::string long_title(256, 'A');
    EXPECT_THROW(Movie(1, long_title), std::invalid_argument);
}