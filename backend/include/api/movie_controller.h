#pragma once

#include "services/catalog_service.h"

namespace MovieBooking
{

class MovieController
{
public:
    static void RegisterRoutes(CatalogService& catalogService);
};

}