#pragma once

#include "services/catalog_service.h"

namespace MovieBooking
{

class ScreeningController
{
public:
    static void RegisterRoutes(CatalogService& catalogService);
};

}