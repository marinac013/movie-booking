#ifndef THEATER_H
#define THEATER_H

#include <string>

namespace MovieBooking
{

class Theater
{
public:
    static constexpr uint SEAT_CAPACITY = 20;

    Theater(uint id, const std::string& name);

    uint GetId() const;
    const std::string& GetName() const;
    uint GetCapacity() const;

private:
    uint id;
    std::string name;
};

}

#endif // THEATER_H