#pragma once

#include "services/catalog_service.h"

namespace MovieBooking
{

class TheaterController
{
public:
    static void RegisterRoutes(CatalogService& catalogService);
};

}