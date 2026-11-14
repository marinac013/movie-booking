#ifndef SEAT_H
#define SEAT_H

#include <string>

namespace MovieBooking
{

class Seat
{
public:
    explicit Seat(const std::string& id);

    const std::string& GetId() const;

private:
    std::string id;
};

}

#endif // SEAT_H