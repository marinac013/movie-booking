#ifndef SCREENING_H
#define SCREENING_H

#include "domain/movie.h"
#include "domain/theater.h"

#include <chrono>

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

    uint GetId() const;
    const Movie& GetMovie() const;
    const Theater& GetTheater() const;
    std::chrono::system_clock::time_point GetStartTime() const;

private:
    uint id;
    Movie movie;
    Theater theater;
    std::chrono::system_clock::time_point startTime;
};

}

#endif // SCREENING_H