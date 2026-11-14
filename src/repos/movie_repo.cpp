#include "repos/movie_repo.h"

namespace MovieBooking
{

bool MovieRepository::Add(const Movie& movie)
{
    const auto result = this->movies.emplace(movie.GetId(), movie);

    return result.second;
}

std::optional<Movie> MovieRepository::FindById(uint id) const
{
    const auto it = this->movies.find(id);

    if (it == this->movies.end())
    {
        return std::nullopt;
    }

    return it->second;
}

std::vector<Movie> MovieRepository::GetAll() const
{
    std::vector<Movie> movies;

    movies.reserve(this->movies.size());

    for (const auto& entry : this->movies)
    {
        movies.push_back(entry.second);
    }

    return movies;
}

bool MovieRepository::Exists(uint id) const
{
    return this->movies.find(id) != this->movies.end();
}

}