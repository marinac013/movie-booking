#include "services/catalog_service.h"

#include <gtest/gtest.h>

#include <chrono>

using namespace MovieBooking;

class CatalogServiceTests : public ::testing::Test
{
protected:
    MovieRepository movieRepository;
    TheaterRepository theaterRepository;
    ScreeningRepository screeningRepository;

    CatalogService service {
        movieRepository,
        theaterRepository,
        screeningRepository
    };

    void SetUp() override
    {
        Movie matrix(1, "The Matrix");
        Movie starWars(3, "Star Wars: A New Hope");

        Theater cinestar(1, "Cinestar");
        Theater cineplexx(2, "Cineplexx");

        movieRepository.Add(matrix);
        movieRepository.Add(starWars);

        theaterRepository.Add(cinestar);
        theaterRepository.Add(cineplexx);

        const auto startTime = std::chrono::system_clock::now();

        screeningRepository.Add(
            Screening(1, matrix, cinestar, startTime));

        screeningRepository.Add(
            Screening(2, matrix, cinestar, startTime));

        screeningRepository.Add(
            Screening(3, matrix, cineplexx, startTime));

        screeningRepository.Add(
            Screening(4, starWars, cineplexx, startTime));
    }
};

TEST_F(CatalogServiceTests, GetMovies)
{
    const auto movies = service.GetMovies();

    ASSERT_EQ(movies.size(), 2);
}

TEST_F(CatalogServiceTests, GetExistingMovieById)
{
    const auto movie = service.GetMovieById(1);

    ASSERT_TRUE(movie.has_value());
    EXPECT_EQ(movie->GetId(), 1);
    EXPECT_EQ(movie->GetTitle(), "The Matrix");
}

TEST_F(CatalogServiceTests, GetNonexistentMovieById)
{
    const auto movie = service.GetMovieById(100);

    EXPECT_FALSE(movie.has_value());
}

TEST_F(CatalogServiceTests, GetTheatersShowingMovie)
{
    const auto theaters = service.GetTheatersShowingMovie(1);

    ASSERT_EQ(theaters.size(), 2);
}

TEST_F(CatalogServiceTests, GetTheatersShowingMovieReturnsUniqueTheaters)
{
    const auto theaters = service.GetTheatersShowingMovie(1);

    int cinestarCount = 0;

    for (const auto& theater : theaters)
    {
        if (theater.GetId() == 1)
        {
            ++cinestarCount;
        }
    }

    EXPECT_EQ(cinestarCount, 1);
}

TEST_F(CatalogServiceTests, GetTheatersForMovieWithoutScreenings)
{
    const auto theaters = service.GetTheatersShowingMovie(100);

    EXPECT_TRUE(theaters.empty());
}

TEST_F(CatalogServiceTests, GetScreeningsForMovie)
{
    const auto screenings = service.GetScreeningsForMovie(1);

    ASSERT_EQ(screenings.size(), 3);

    for (const auto& screening : screenings)
    {
        EXPECT_EQ(screening.GetMovie().GetId(), 1);
    }
}

TEST_F(CatalogServiceTests, GetScreeningsForTheater)
{
    const auto screenings = service.GetScreeningsForTheater(2);

    ASSERT_EQ(screenings.size(), 2);

    for (const auto& screening : screenings)
    {
        EXPECT_EQ(screening.GetTheater().GetId(), 2);
    }
}

TEST_F(CatalogServiceTests, GetScreeningsForNonexistentMovie)
{
    const auto screenings = service.GetScreeningsForMovie(100);

    EXPECT_TRUE(screenings.empty());
}

TEST_F(CatalogServiceTests, GetScreeningsForNonexistentTheater)
{
    const auto screenings = service.GetScreeningsForTheater(100);

    EXPECT_TRUE(screenings.empty());
}

TEST_F(CatalogServiceTests, GetExistingScreeningById)
{
    const auto screening = service.GetScreeningById(1);

    ASSERT_TRUE(screening.has_value());
    EXPECT_EQ(screening->GetId(), 1);
    EXPECT_EQ(screening->GetMovie().GetId(), 1);
    EXPECT_EQ(screening->GetTheater().GetId(), 1);
}

TEST_F(CatalogServiceTests, GetNonexistentScreeningById)
{
    const auto screening = service.GetScreeningById(100);

    EXPECT_FALSE(screening.has_value());
}
