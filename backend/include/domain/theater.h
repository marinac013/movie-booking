#ifndef THEATER_H
#define THEATER_H

#include <string>

namespace MovieBooking
{

/** @brief Represents a theater. */
class Theater
{
public:
    /** @brief The maximum number of seats in the theater. */
    static constexpr uint SEAT_CAPACITY = 20;
    /** @brief Constructs a theater. */
    Theater(uint id, const std::string& name);

    /** @brief Returns the theater ID. */
    uint GetId() const;
    /** @brief Returns the theater name. */
    const std::string& GetName() const;
    /** @brief Returns the theater capacity. */
    uint GetCapacity() const;

private:
    /** @brief The theater ID. */
    uint id;
    /** @brief The theater name. */
    std::string name;
};

}

#endif // THEATER_H