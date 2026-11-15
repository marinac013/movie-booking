#include "repos/theater_repo.h"

namespace MovieBooking
{

bool TheaterRepository::Add(const Theater& theater)
{
    const auto result = this->theaters.emplace(theater.GetId(), theater);

    return result.second;
}

std::optional<Theater> TheaterRepository::FindById(uint id) const
{
    const auto it = this->theaters.find(id);

    if (it == this->theaters.end())
    {
        return std::nullopt;
    }

    return it->second;
}

std::vector<Theater> TheaterRepository::GetAll() const
{
    std::vector<Theater> theaters;

    theaters.reserve(this->theaters.size());

    for (const auto& entry : this->theaters)
    {
        theaters.push_back(entry.second);
    }

    return theaters;
}

bool TheaterRepository::Exists(uint id) const
{
    return this->theaters.find(id) != this->theaters.end();
}

}