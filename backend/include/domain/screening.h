#ifndef SCREENING_H
#define SCREENING_H

#include "domain/movie.h"
#include "domain/theater.h"

#include <chrono>
#include <vector>
#include <unordered_set>

namespace MovieBooking
{

/** @brief Represents a movie screening. */
class Screening
{
public:
    /**
     * @brief Constructs a screening.
     * @param id Unique screening ID.
     * @param movie Movie being screened.
     * @param theater Theater where the screening is held.
     * @param startTime Screening start time.
     */
    Screening(
        uint id,
        const Movie& movie,
        const Theater& theater,
        const std::chrono::system_clock::time_point& startTime);

    /**
     * @brief Returns the ID of the screening.
     * @return The screening ID.
     */
    uint GetId() const;

    /**
     * @brief Returns the movie being screened.
     * @return The movie.
     */
    const Movie& GetMovie() const;

    /**
     * @brief Returns the theater where this screening is held.
     * @return The theater.
     */
    const Theater& GetTheater() const;

    /**
     * @brief Returns the start time of the screening.
     * @return The start time.
     */
    std::chrono::system_clock::time_point GetStartTime() const;
    /**
     * @brief Returns all currently available seat IDs.
     * @return A vector containing available seat IDs.
     */
    std::vector<std::string> GetAvailableSeats() const;

    /**
    * @brief Checks whether a seat ID belongs to this screening.
    * @param seatId Seat identifier, e.g. A1.
    * @return True if the identifier is valid.
    */
    bool IsValidSeatId(const std::string& seatId) const;

    /**
    * @brief Checks whether a seat is available.
    * @param seatId Seat identifier.
    * @return True if the seat is valid and not booked.
    */
    bool IsSeatAvailable(const std::string& seatId) const;

    /**
    * @brief Reserves all requested seats if they are available.
    * @param seatIds IDs of the seats to reserve.
    * @return True if all seats were reserved; otherwise false.
    */
    bool ReserveSeats(const std::vector<std::string>& seatIds) ;

private:
    /** @brief The screening ID. */
    uint id;
    /** @brief The movie being screened. */
    Movie movie;
    /** @brief The theater where the screening is held. */
    Theater theater;
    /** @brief The start time of the screening. */
    std::chrono::system_clock::time_point startTime;
    /** @brief The set of booked seat IDs. */
    std::unordered_set<std::string> bookedSeatIds;
};

}

#endif // SCREENING_H