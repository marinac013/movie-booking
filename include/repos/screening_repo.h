#include "domain/screening.h"

#include <optional>
#include <unordered_map>
#include <vector>

namespace MovieBooking
{

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

private:
    std::unordered_map<uint, Screening> screenings;
};

}