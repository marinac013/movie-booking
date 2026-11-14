#ifndef SCREENING_H
#define SCREENING_H

#include "domain/movie.h"
#include "domain/theater.h"

#include <chrono>
#include <vector>
#include <unordered_set>

namespace MovieBooking
{

class Screening
{
public:
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
    uint id;
    Movie movie;
    Theater theater;
    std::chrono::system_clock::time_point startTime;
    std::unordered_set<std::string> bookedSeatIds;

};

}

#endif // SCREENING_H