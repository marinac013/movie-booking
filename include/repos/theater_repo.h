#pragma once

#include "domain/theater.h"

#include <optional>
#include <unordered_map>
#include <vector>

namespace MovieBooking
{

class TheaterRepository
{
public:
    /**
     * @brief Adds a theater to the repository.
     * @param theater Theater to add.
     * @return True if the theater was added, false if its ID already exists.
     */
    bool Add(const Theater& theater);

    /**
     * @brief Finds a theater by its ID.
     * @param id Theater ID.
     * @return The theater if found; otherwise std::nullopt.
     */
    std::optional<Theater> FindById(uint id) const;

    /**
     * @brief Returns all stored theaters.
     * @return A vector containing all theaters.
     */
    std::vector<Theater> GetAll() const;

    /**
     * @brief Checks whether a theater with the specified ID exists.
     * @param id Theater ID.
     * @return True if the theater exists.
     */
    bool Exists(uint id) const;

private:
    std::unordered_map<uint, Theater> theaters;
};

}