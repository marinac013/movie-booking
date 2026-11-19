#pragma once

#include "domain/screening.h"

#include <optional>
#include <unordered_map>
#include <shared_mutex>
#include <memory>
#include <mutex>
#include <vector>

namespace MovieBooking
{

/** @brief Manages storage and retrieval of screening data. */
class ScreeningRepository
{
public:
    /**
     * @brief Adds a screening to the repository.
     * @param screening Screening to add.
     * @return True if the screening was added, false if its ID already exists.
     */
    bool Add(const Screening& screening);

    /**
     * @brief Finds a screening by its ID.
     * @param id Screening ID.
     * @return The screening if found; otherwise std::nullopt.
     */
    std::optional<Screening> FindById(uint id) const;

    /**
     * @brief Returns all stored screenings.
     * @return A vector containing all screenings.
     */
    std::vector<Screening> GetAll() const;

    /**
     * @brief Checks whether a screening with the specified ID exists.
     * @param id Screening ID.
     * @return True if the screening exists.
     */
    bool Exists(uint id) const;

    /**
    * @brief Updates an existing screening.
    * @param screening Updated screening.
    * @return True if the screening existed and was updated.
    */
    bool Update(const Screening& screening);

    /**
     * @brief Acquires the exclusive lock for a screening.
     *
     * The returned lock must remain alive for the entire operation
     * that requires exclusive access to the screening.
     *
     * @param screeningId Screening ID.
     * @return An acquired unique lock.
     */
    std::unique_lock<std::mutex> LockFor(uint screeningId) const;

private:
    /** @brief The map storing all screenings. */
    std::unordered_map<uint, Screening> screenings;
    /** @brief The mutex protecting the screening map. */
    mutable std::shared_mutex repositoryMutex;
    /** @brief The map storing locks for individual screenings. */
    mutable std::unordered_map<uint, std::shared_ptr<std::mutex>> screeningLocks;
    /** @brief The mutex protecting the screening locks map. */
    mutable std::mutex locksMutex;
};

}