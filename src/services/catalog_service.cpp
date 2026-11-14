#include "services/catalog_service.h"

#include <unordered_set>

namespace MovieBooking
{

CatalogService::CatalogService(
    MovieRepository& movieRepository,
    TheaterRepository& theaterRepository,
    ScreeningRepository& screeningRepository)
    : movieRepository(movieRepository),
      theaterRepository(theaterRepository),
      screeningRepository(screeningRepository)
{
}

std::vector<Movie> CatalogService::GetMovies() const
{
    return this->movieRepository.GetAll();
}

std::optional<Movie> CatalogService::GetMovieById(uint movieId) const
{
    return this->movieRepository.FindById(movieId);
}

std::vector<Theater> CatalogService::GetTheatersShowingMovie(uint movieId) const
{
    std::vector<Theater> theaters;
    std::unordered_set<uint> theaterIds;

    const auto screenings = this->screeningRepository.GetAll();

    for (const auto& screening : screenings)
    {
        if (screening.GetMovie().GetId() != movieId)
        {
            continue;
        }

        const auto theater = screening.GetTheater();
        const uint theaterId = theater.GetId();

        if (theaterIds.insert(theaterId).second)
        {
            theaters.push_back(theater);
        }
    }

    return theaters;
}

std::vector<Screening> CatalogService::GetScreeningsForMovie(uint movieId) const
{
    std::vector<Screening> result;

    const auto screenings = this->screeningRepository.GetAll();

    for (const auto& screening : screenings)
    {
        if (screening.GetMovie().GetId() == movieId)
        {
            result.push_back(screening);
        }
    }

    return result;
}

std::vector<Screening> CatalogService::GetScreeningsForTheater(uint theaterId) const
{
    std::vector<Screening> result;

    const auto screenings = this->screeningRepository.GetAll();

    for (const auto& screening : screenings)
    {
        if (screening.GetTheater().GetId() == theaterId)
        {
            result.push_back(screening);
        }
    }

    return result;
}

}