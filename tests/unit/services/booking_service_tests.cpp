#include "services/booking_service.h"
#include "repos/movie_repo.h"
#include "repos/theater_repo.h"

#include <gtest/gtest.h>

#include <chrono>
#include <string>
#include <vector>

using namespace MovieBooking;

class BookingServiceTests : public ::testing::Test
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

TEST_F(BookingServiceTests, BookSingleSeat)
{
    const auto result = service.BookSeats(1, { "A1" });

    ASSERT_TRUE(result.IsSuccess());
    ASSERT_TRUE(result.booking.has_value());

    EXPECT_EQ(result.booking->GetScreeningId(), 1);
    EXPECT_EQ(result.booking->GetSeatIds().size(), 1);
    EXPECT_EQ(result.booking->GetSeatIds().at(0), "A1");
}

TEST_F(BookingServiceTests, BookMultipleSeats)
{
    const auto result = service.BookSeats(1, { "A1", "A2", "A3" });

    ASSERT_TRUE(result.IsSuccess());
    ASSERT_TRUE(result.booking.has_value());

    EXPECT_EQ(result.booking->GetSeatIds().size(), 3);
}

TEST_F(BookingServiceTests, RejectBookingForNonexistentScreening)
{
    const auto result = service.BookSeats(100, { "A1" });

    EXPECT_EQ(result.status, BookingStatus::ScreeningNotFound);
    EXPECT_FALSE(result.booking.has_value());
}

TEST_F(BookingServiceTests, RejectEmptySeatSelection)
{
    const auto result = service.BookSeats(1, {});

    EXPECT_EQ(result.status, BookingStatus::EmptySeatSelection);
}

TEST_F(BookingServiceTests, RejectInvalidSeat)
{
    const auto result = service.BookSeats(1, { "A21" });

    EXPECT_EQ(result.status, BookingStatus::InvalidSeat);
}

TEST_F(BookingServiceTests, RejectDuplicateSeats)
{
    const auto result = service.BookSeats(1, { "A1", "A1" });

    EXPECT_EQ(result.status, BookingStatus::DuplicateSeat);
}

TEST_F(BookingServiceTests, RejectAlreadyBookedSeat)
{
    const auto firstBooking = service.BookSeats(1, { "A1" });

    ASSERT_TRUE(firstBooking.IsSuccess());

    const auto secondBooking = service.BookSeats(1, { "A1" });

    EXPECT_EQ(secondBooking.status, BookingStatus::SeatUnavailable);
}

TEST_F(BookingServiceTests, FailedBookingDoesNotReserveAnySeats)
{
    // Reserve A2 first.
    const auto firstBooking = service.BookSeats(1, { "A2" });

    ASSERT_TRUE(firstBooking.IsSuccess());

    // A1 and A3 must remain available if the complete request fails.
    const auto secondBooking = service.BookSeats(1, { "A1", "A2", "A3" });

    EXPECT_EQ(secondBooking.status, BookingStatus::SeatUnavailable);

    const auto screening = screeningRepository.FindById(1);

    ASSERT_TRUE(screening.has_value());

    EXPECT_TRUE(screening->IsSeatAvailable("A1"));
    EXPECT_FALSE(screening->IsSeatAvailable("A2"));
    EXPECT_TRUE(screening->IsSeatAvailable("A3"));
}

TEST_F(BookingServiceTests, SameSeatCanBeBookedForDifferentScreenings)
{
    const auto firstBooking = service.BookSeats(1, { "A1" });
    const auto secondBooking = service.BookSeats(2, { "A1" });

    EXPECT_TRUE(firstBooking.IsSuccess());
    EXPECT_TRUE(secondBooking.IsSuccess());
}

TEST_F(BookingServiceTests, SuccessfulBookingIsStored)
{
    const auto result = service.BookSeats(1, { "A1", "A2" });

    ASSERT_TRUE(result.IsSuccess());
    ASSERT_TRUE(result.booking.has_value());

    const int bookingId = result.booking->GetId();

    EXPECT_TRUE(bookingRepository.Exists(bookingId));

    const auto storedBooking = bookingRepository.FindById(bookingId);

    ASSERT_TRUE(storedBooking.has_value());
    EXPECT_EQ(storedBooking->GetScreeningId(), 1);
    EXPECT_EQ(storedBooking->GetSeatIds().size(), 2);
}

TEST_F(BookingServiceTests, BookingIdsAreUnique)
{
    const auto firstBooking = service.BookSeats(1, { "A1" });
    const auto secondBooking = service.BookSeats(1, { "A2" });

    ASSERT_TRUE(firstBooking.IsSuccess());
    ASSERT_TRUE(secondBooking.IsSuccess());

    EXPECT_NE(
        firstBooking.booking->GetId(),
        secondBooking.booking->GetId());
}

TEST_F(BookingServiceTests, FailedBookingDoesNotCreateBookingRecord)
{
    const auto result = service.BookSeats(1, { "A21" });

    EXPECT_FALSE(result.IsSuccess());
    EXPECT_TRUE(bookingRepository.GetAll().empty());
}

TEST_F(BookingServiceTests, AllTwentySeatsCanBeBooked)
{
    std::vector<std::string> seats;

    for (int i = 1; i <= 20; ++i)
    {
        seats.push_back("A" + std::to_string(i));
    }

    const auto result = service.BookSeats(1, seats);

    ASSERT_TRUE(result.IsSuccess());

    const auto screening = screeningRepository.FindById(1);

    ASSERT_TRUE(screening.has_value());
    EXPECT_TRUE(screening->GetAvailableSeats().empty());
}