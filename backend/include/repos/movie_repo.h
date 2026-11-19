#pragma once

#include "domain/movie.h"

#include <optional>
#include <unordered_map>
#include <vector>

namespace MovieBooking
{

/** @brief Manages storage and retrieval of movie data. */
class MovieRepository
{
public:
    /**
     * @brief Adds a movie to the repository.
     * @param movie Movie to add.
     * @return True if the movie was added, false if its ID already exists.
     */
    bool Add(const Movie& movie);

    /**
     * @brief Finds a movie by its ID.
     * @param id Movie ID.
     * @return The movie if found; otherwise std::nullopt.
     */
    std::optional<Movie> FindById(uint id) const;

    /**
     * @brief Returns all stored movies.
     * @return A vector containing all movies.
     */
    std::vector<Movie> GetAll() const;

    /**
     * @brief Checks whether a movie with the specified ID exists.
     * @param id Movie ID.
     * @return True if the movie exists.
     */
    bool Exists(uint id) const;

private:
    /** @brief The map storing all movies. */
    std::unordered_map<uint, Movie> movies;
};

}