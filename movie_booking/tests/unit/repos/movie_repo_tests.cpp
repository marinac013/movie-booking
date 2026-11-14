#include "repos/movie_repo.h"

#include <gtest/gtest.h>

#include <optional>

using namespace MovieBooking;

TEST(MovieRepositoryTests, AddMovie)
{
    MovieRepository repo;
    Movie movie(1, "The Matrix");

    EXPECT_TRUE(repo.Add(movie));
    EXPECT_TRUE(repo.Exists(1));
}

TEST(MovieRepositoryTests, RejectDuplicateMovieId)
{
    MovieRepository repo;

    Movie first(1, "The Matrix");
    Movie second(1, "Interstellar");

    EXPECT_TRUE(repo.Add(first));
    EXPECT_FALSE(repo.Add(second));
}

TEST(MovieRepositoryTests, DuplicateIdDoesNotOverwriteExistingMovie)
{
    MovieRepository repo;

    Movie first(1, "The Matrix");
    Movie second(1, "Interstellar");

    repo.Add(first);
    repo.Add(second);

    const auto result = repo.FindById(1);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->GetTitle(), "The Matrix");
}

TEST(MovieRepositoryTests, FindExistingMovie)
{
    MovieRepository repo;
    Movie movie(1, "The Matrix");

    repo.Add(movie);

    const auto result = repo.FindById(1);

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->GetId(), 1);
    EXPECT_EQ(result->GetTitle(), "The Matrix");
}

TEST(MovieRepositoryTests, FindNonexistentMovie)
{
    MovieRepository repo;

    const auto result = repo.FindById(100);

    EXPECT_FALSE(result.has_value());
}

TEST(MovieRepositoryTests, GetAllMoviesWhenRepositoryIsEmpty)
{
    MovieRepository repo;

    const auto movies = repo.GetAll();

    EXPECT_TRUE(movies.empty());
}

TEST(MovieRepositoryTests, GetAllMovies)
{
    MovieRepository repo;

    repo.Add(Movie(1, "The Matrix"));
    repo.Add(Movie(2, "Interstellar"));
    repo.Add(Movie(3, "Inception"));

    const auto movies = repo.GetAll();

    ASSERT_EQ(movies.size(), 3);
}

TEST(MovieRepositoryTests, ExistsReturnsTrueForExistingMovie)
{
    MovieRepository repo;

    repo.Add(Movie(1, "The Matrix"));

    EXPECT_TRUE(repo.Exists(1));
}

TEST(MovieRepositoryTests, ExistsReturnsFalseForNonexistentMovie)
{
    MovieRepository repo;

    EXPECT_FALSE(repo.Exists(1));
}