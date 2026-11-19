#ifndef MOVIE_H
#define MOVIE_H

#include <string>

namespace MovieBooking
{

/** @brief Represents a movie. */
class Movie 
{
public:
    /** @brief Constructs a movie. */
    Movie(uint id, const std::string& title);

    /** @brief Returns the movie ID. */
    uint GetId() const;
    /** @brief Returns the movie title. */
    const std::string& GetTitle() const;

private:
    /** @brief The movie ID. */
    uint id;
    /** @brief The movie title. */
    std::string title;
};

}

#endif // MOVIE_H