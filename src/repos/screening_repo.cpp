#include "repos/screening_repo.h"

namespace MovieBooking
{

bool ScreeningRepository::Add(const Screening& screening)
{
    const auto result = this->screenings.emplace(screening.GetId(), screening);

    return result.second;
}

std::optional<Screening> ScreeningRepository::FindById(uint id) const
{
    const auto it = this->screenings.find(id);

    if (it == this->screenings.end())
    {
        return std::nullopt;
    }

    return it->second;
}

std::vector<Screening> ScreeningRepository::GetAll() const
{
    std::vector<Screening> screenings;


    screenings.reserve(this->screenings.size());

    for (const auto& entry : this->screenings)
    {
        screenings.push_back(entry.second);
    }

    return screenings;
}

bool ScreeningRepository::Exists(uint id) const
{
    return this->screenings.find(id) != this->screenings.end();
}

}