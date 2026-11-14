#include "repos/theater_repo.h"

#include <gtest/gtest.h>

using namespace MovieBooking;

TEST(TheaterRepositoryTests, AddTheater)
{
    TheaterRepository repo;
    Theater theater(1, "Cinestar");

    EXPECT_TRUE(repo.Add(theater));
    EXPECT_TRUE(repo.Exists(1));
}

TEST(TheaterRepositoryTests, RejectDuplicateTheaterId)
{
    TheaterRepository repo;

    Theater first(1, "Cinestar");
    Theater second(1, "Cineplexx");

    EXPECT_TRUE(repo.Add(first));
    EXPECT_FALSE(repo.Add(second));
}

TEST(TheaterRepositoryTests, DuplicateIdDoesNotOverwriteExistingTheater)
{
    TheaterRepository repo;

    Theater first(1, "Cinestar");
    Theater second(1, "Cineplexx");

    repo.Add(first);
    repo.Add(second);

    const auto result = repo.FindById(1);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->GetName(), "Cinestar");
}

TEST(TheaterRepositoryTests, FindExistingTheater)
{
    TheaterRepository repo;
    Theater theater(1, "Cinestar");

    repo.Add(theater);

    const auto result = repo.FindById(1);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->GetId(), 1);
    EXPECT_EQ(result->GetName(), "Cinestar");
}

TEST(TheaterRepositoryTests, FindNonexistentTheater)
{
    TheaterRepository repo;

    const auto result = repo.FindById(100);

    EXPECT_FALSE(result.has_value());
}

TEST(TheaterRepositoryTests, GetAllTheatersWhenRepositoryIsEmpty)
{
    TheaterRepository repo;

    const auto theaters = repo.GetAll();

    EXPECT_TRUE(theaters.empty());
}

TEST(TheaterRepositoryTests, GetAllTheaters)
{
    TheaterRepository repo;

    repo.Add(Theater(1, "Cinema City"));
    repo.Add(Theater(2, "Cineplexx"));
    repo.Add(Theater(3, "Vilin Grad"));

    const auto theaters = repo.GetAll();

    ASSERT_EQ(theaters.size(), 3);
}

TEST(TheaterRepositoryTests, ExistsReturnsTrueForExistingTheater)
{
    TheaterRepository repo;

    repo.Add(Theater(1, "Cinema City"));

    EXPECT_TRUE(repo.Exists(1));
}

TEST(TheaterRepositoryTests, ExistsReturnsFalseForNonexistentTheater)
{
    TheaterRepository repo;

    EXPECT_FALSE(repo.Exists(1));
}