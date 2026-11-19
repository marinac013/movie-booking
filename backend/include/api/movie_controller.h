#pragma once

#include "services/catalog_service.h"

namespace MovieBooking
{

class MovieController
{
public:
    /**
     * @brief Registers the movie routes.
     * @param catalogService The catalog service.
     */
    static void RegisterRoutes(CatalogService& catalogService);
};

}