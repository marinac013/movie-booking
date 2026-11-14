#include "repos/booking_repo.h"

#include <gtest/gtest.h>

#include <chrono>

using namespace MovieBooking;

namespace
{

Booking CreateBooking(uint id)
{
    return Booking(
        id,
        1,
        { "A1", "A2" },
        std::chrono::system_clock::now());
}

}

TEST(BookingRepositoryTests, AddBooking)
{
    BookingRepository repo;

    EXPECT_TRUE(repo.Add(CreateBooking(1)));
    EXPECT_TRUE(repo.Exists(1));
}

TEST(BookingRepositoryTests, RejectDuplicateBookingId)
{
    BookingRepository repo;

    EXPECT_TRUE(repo.Add(CreateBooking(1)));
    EXPECT_FALSE(repo.Add(CreateBooking(1)));
}

TEST(BookingRepositoryTests, FindExistingBooking)
{
    BookingRepository repo;

    repo.Add(CreateBooking(1));

    const auto result = repo.FindById(1);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->GetId(), 1);
    EXPECT_EQ(result->GetScreeningId(), 1);
    EXPECT_EQ(result->GetSeatIds().size(), 2);
}

TEST(BookingRepositoryTests, FindNonExistentBooking)
{
    BookingRepository repo;

    EXPECT_FALSE(repo.FindById(100).has_value());
}

TEST(BookingRepositoryTests, GetAllBookings)
{
    BookingRepository repo;

    repo.Add(CreateBooking(1));
    repo.Add(CreateBooking(2));

    const auto bookings = repo.GetAll();

    EXPECT_EQ(bookings.size(), 2);
}

TEST(BookingRepositoryTests, GetAllBookingsWhenRepositoryIsEmpty)
{
    BookingRepository repo;

    EXPECT_TRUE(repo.GetAll().empty());
}

TEST(BookingRepositoryTests, ExistsReturnsTrueForExistingBooking)
{
    BookingRepository repo;

    repo.Add(CreateBooking(1));

    EXPECT_TRUE(repo.Exists(1));
}

TEST(BookingRepositoryTests, ExistsReturnsFalseForNonexistentBooking)
{
    BookingRepository repo;

    EXPECT_FALSE(repo.Exists(1));
}