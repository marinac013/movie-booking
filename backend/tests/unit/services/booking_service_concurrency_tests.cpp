#include "services/booking_service.h"
#include "repos/screening_repo.h"
#include "repos/booking_repo.h"
#include "repos/movie_repo.h"
#include "repos/theater_repo.h"
#include "domain/movie.h"
#include "domain/theater.h"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

using namespace MovieBooking;

class BookingServiceConcurrencyTests : public ::testing::Test
{
protected:
    MovieRepository movieRepository;
    TheaterRepository theaterRepository;
    ScreeningRepository screeningRepository;
    BookingRepository bookingRepository;

    BookingService service {
        screeningRepository,
        bookingRepository
    };

    void SetUp() override
    {
        Movie movie(1, "The Matrix");
        Theater theater(1, "Cinestar");

        const auto startTime = std::chrono::system_clock::now();

        movieRepository.Add(movie);
        theaterRepository.Add(theater);

        screeningRepository.Add(
            Screening(1, movie, theater, startTime));

        screeningRepository.Add(
            Screening(2, movie, theater, startTime));
    }
};

TEST_F(
    BookingServiceConcurrencyTests,
    OnlyOneThreadCanBookTheSameSeat)
{
    constexpr uint THREAD_COUNT = 100;

    std::atomic<uint> successfulBookings { 0 };

    std::vector<std::thread> threads;

    for (uint i = 0; i < THREAD_COUNT; ++i)
    {
        threads.emplace_back([this, &successfulBookings]()
        {
            const auto result = this->service.BookSeats(1, { "A1" });

            if (result.IsSuccess())
            {
                successfulBookings.fetch_add(1);
            }
        });
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    EXPECT_EQ(successfulBookings.load(), 1);

    EXPECT_EQ(bookingRepository.GetAll().size(), 1);

    const auto screening = screeningRepository.FindById(1);

    ASSERT_TRUE(screening.has_value());

    EXPECT_FALSE(screening->IsSeatAvailable("A1"));
    EXPECT_EQ(screening->GetAvailableSeats().size(), 19);
}

TEST_F(
    BookingServiceConcurrencyTests,
    OverlappingSeatRequestsAreAtomic)
{
    std::atomic<int> successfulBookings { 0 };

    std::thread threadA([this, &successfulBookings]()
    {
        const auto result = this->service.BookSeats(1, { "A1", "A2" });

        if (result.IsSuccess())
        {
            successfulBookings.fetch_add(1);
        }
    });

    std::thread threadB([this, &successfulBookings]()
    {
        const auto result = this->service.BookSeats(1, { "A2", "A3" });

        if (result.IsSuccess())
        {
            successfulBookings.fetch_add(1);
        }
    });

    threadA.join();
    threadB.join();

    EXPECT_EQ(successfulBookings.load(), 1);
    EXPECT_EQ(bookingRepository.GetAll().size(), 1);

    const auto screening = screeningRepository.FindById(1);

    ASSERT_TRUE(screening.has_value());

    EXPECT_EQ(screening->GetAvailableSeats().size(), 18);
    EXPECT_FALSE(screening->IsSeatAvailable("A2"));
}

TEST_F(
    BookingServiceConcurrencyTests,
    DifferentScreeningsCanBeBookedSimultaneously)
{
    std::atomic<int> successfulBookings { 0 };

    std::thread threadA([this, &successfulBookings]()
    {
        const auto result = this->service.BookSeats(1, { "A1" });

        if (result.IsSuccess())
        {
            successfulBookings.fetch_add(1);
        }
    });

    std::thread threadB([this, &successfulBookings]()
    {
        const auto result = this->service.BookSeats(2, { "A1" });

        if (result.IsSuccess())
        {
            successfulBookings.fetch_add(1);
        }
    });

    threadA.join();
    threadB.join();

    EXPECT_EQ(successfulBookings.load(), 2);
    EXPECT_EQ(bookingRepository.GetAll().size(), 2);
}

TEST_F(
    BookingServiceConcurrencyTests,
    ConcurrentBookingsReceiveUniqueIds)
{
    constexpr int THREAD_COUNT = 20;

    std::vector<std::thread> threads;

    std::atomic<int> successfulBookings { 0 };

    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        threads.emplace_back([this, i, &successfulBookings]()
        {
            const std::string seatId = "A" + std::to_string(i + 1);

            const auto result = this->service.BookSeats(1, { seatId });

            if (result.IsSuccess())
            {
                successfulBookings.fetch_add(1);
            }
        });
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    EXPECT_EQ(successfulBookings.load(), THREAD_COUNT);

    const auto bookings = bookingRepository.GetAll();

    ASSERT_EQ(bookings.size(), THREAD_COUNT);

    std::unordered_set<int> bookingIds;

    for (const auto& booking : bookings)
    {
        bookingIds.insert(booking.GetId());
    }

    EXPECT_EQ(bookingIds.size(), THREAD_COUNT);
}