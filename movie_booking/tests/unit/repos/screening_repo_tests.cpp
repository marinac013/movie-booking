#include "repos/screening_repo.h"

#include <gtest/gtest.h>

#include <chrono>

using namespace MovieBooking;

namespace
{

Screening CreateScreening(int id)
{
    Movie movie(1, "The Matrix");
    Theater theater(1, "Cinestar");

    const auto startTime = std::chrono::system_clock::now();

    return Screening(id, movie, theater, startTime);
}

}

TEST(ScreeningRepositoryTests, AddScreening)
{
    ScreeningRepository repo;
    Screening screening = CreateScreening(1);

    EXPECT_TRUE(repo.Add(screening));
    EXPECT_TRUE(repo.Exists(1));
}

TEST(ScreeningRepositoryTests, RejectDuplicateScreeningId)
{
    ScreeningRepository repo;

    Screening first = CreateScreening(1);
    Screening second = CreateScreening(1);

    EXPECT_TRUE(repo.Add(first));
    EXPECT_FALSE(repo.Add(second));
}

TEST(ScreeningRepositoryTests, DuplicateIdDoesNotOverwriteExistingScreening)
{
    ScreeningRepository repo;

    Movie firstMovie(1, "The Matrix");
    Movie secondMovie(2, "Star Wars: A New Hope");

    Theater theater(1, "Cinema City");

    const auto startTime = std::chrono::system_clock::now();

    Screening first(1, firstMovie, theater, startTime);
    Screening second(1, secondMovie, theater, startTime);

    repo.Add(first);
    repo.Add(second);

    const auto result = repo.FindById(1);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->GetMovie().GetTitle(), "The Matrix");
}

TEST(ScreeningRepositoryTests, FindExistingScreening)
{
    ScreeningRepository repo;
    Screening screening = CreateScreening(1);

    repo.Add(screening);

    const auto result = repo.FindById(1);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->GetId(), 1);
}

TEST(ScreeningRepositoryTests, FindNonexistentScreening)
{
    ScreeningRepository repo;

    const auto result = repo.FindById(100);

    EXPECT_FALSE(result.has_value());
}

TEST(ScreeningRepositoryTests, GetAllScreeningsWhenRepositoryIsEmpty)
{
    ScreeningRepository repo;

    const auto screenings = repo.GetAll();

    EXPECT_TRUE(screenings.empty());
}

TEST(ScreeningRepositoryTests, GetAllScreenings)
{
    ScreeningRepository repo;

    repo.Add(CreateScreening(1));
    repo.Add(CreateScreening(2));
    repo.Add(CreateScreening(3));

    const auto screenings = repo.GetAll();

    ASSERT_EQ(screenings.size(), 3);
}

TEST(ScreeningRepositoryTests, ExistsReturnsTrueForExistingScreening)
{
    ScreeningRepository repo;

    repo.Add(CreateScreening(1));

    EXPECT_TRUE(repo.Exists(1));
}

TEST(ScreeningRepositoryTests, ExistsReturnsFalseForNonexistentScreening)
{
    ScreeningRepository repo;

    EXPECT_FALSE(repo.Exists(1));
}