#ifndef MOVIE_H
#define MOVIE_H

#include <string>

namespace MovieBooking
{

class Movie 
{
public:
    Movie(uint id, const std::string& title);

    uint GetId() const;
    const std::string& GetTitle() const;

private:
    uint id;
    std::string title;
};

}

#endif // MOVIE_H