#pragma once

#include "repos/movie_repo.h"
#include "repos/theater_repo.h"
#include "repos/screening_repo.h"

#include <optional>
#include <vector>

namespace MovieBooking
{

class CatalogService
{
public:
    /**
     * @brief Constructs the catalog service.
     * @param movieRepository Repository used to access movies.
     * @param theaterRepository Repository used to access theaters.
     * @param screeningRepository Repository used to access screenings.
     */
    CatalogService(
        MovieRepository& movieRepository,
        TheaterRepository& theaterRepository,
        ScreeningRepository& screeningRepository);

    /**
     * @brief Returns all movies.
     * @return A vector containing all movies.
     */
    std::vector<Movie> GetMovies() const;

    /**
     * @brief Finds a movie by its ID.
     * @param movieId Movie ID.
     * @return The movie if found; otherwise std::nullopt.
     */
    std::optional<Movie> GetMovieById(uint movieId) const;

    /**
     * @brief Returns all theaters showing a particular movie.
     * @param movieId Movie ID.
     * @return A vector containing unique theaters showing the movie.
     */
    std::vector<Theater> GetTheatersShowingMovie(uint movieId) const;

    /**
     * @brief Returns all screenings of a particular movie.
     * @param movieId Movie ID.
     * @return A vector containing matching screenings.
     */
    std::vector<Screening> GetScreeningsForMovie(uint movieId) const;

    /**
     * @brief Returns all screenings at a particular theater.
     * @param theaterId Theater ID.
     * @return A vector containing matching screenings.
     */
    std::vector<Screening> GetScreeningsForTheater(uint theaterId) const;

private:
    MovieRepository& movieRepository;
    TheaterRepository& theaterRepository;
    ScreeningRepository& screeningRepository;
};

}