#include "domain/movie.h"

#include <stdexcept>

namespace MovieBooking
{

Movie::Movie(uint id, const std::string& title)
    : id(id)
    , title(title)
{
    if (title.empty())
    {
        throw std::invalid_argument("[ Error ] Movie title cannot be empty.");
    }
    
    if (title.size() > 255)
    {
        throw std::invalid_argument("[ Error ] Movie title cannot exceed 255 characters.");
    }
}

uint Movie::GetId() const
{
    return id;
}

const std::string& Movie::GetTitle() const
{
    return title;
}

}