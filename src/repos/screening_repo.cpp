#include "repos/screening_repo.h"

namespace MovieBooking
{

bool ScreeningRepository::Add(const Screening& screening)
{
    std::unique_lock<std::shared_mutex> lock(this->repositoryMutex);

    const auto result = this->screenings.emplace(screening.GetId(), screening);

    return result.second;
}

std::optional<Screening> ScreeningRepository::FindById(uint id) const
{
    std::shared_lock<std::shared_mutex> lock(this->repositoryMutex);
    
    const auto it = this->screenings.find(id);

    if (it == this->screenings.end())
    {
        return std::nullopt;
    }

    return it->second;
}

std::vector<Screening> ScreeningRepository::GetAll() const
{
    std::shared_lock<std::shared_mutex> lock(this->repositoryMutex);
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
    std::shared_lock<std::shared_mutex> lock(this->repositoryMutex);
    return this->screenings.find(id) != this->screenings.end();
}

bool ScreeningRepository::Update(const Screening& screening)
{
    std::unique_lock<std::shared_mutex> lock(this->repositoryMutex);

    const auto it = this->screenings.find(screening.GetId());

    if (it == this->screenings.end())
    {
        return false;
    }

    it->second = screening;

    return true;
}

std::unique_lock<std::mutex> ScreeningRepository::LockFor(uint screeningId) const
{
    std::shared_ptr<std::mutex> screeningMutex;

    {
        std::lock_guard<std::mutex> lock(this->locksMutex);

        auto& mutexPtr = this->screeningLocks[screeningId];

        if (!mutexPtr)
        {
            mutexPtr = std::make_shared<std::mutex>();
        }

        screeningMutex = mutexPtr;
    }

    return std::unique_lock<std::mutex>(*screeningMutex);
}

}