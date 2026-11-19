#ifndef SEAT_H
#define SEAT_H

#include <string>

namespace MovieBooking
{

/** @brief Represents a seat in the theater. */
class Seat
{
public:
    /** @brief Constructs a seat. */
    explicit Seat(const std::string& id);

    /** @brief Returns the seat ID. */
    const std::string& GetId() const;

private:
    /** @brief The seat ID. */
    std::string id;
};

}

#endif // SEAT_H