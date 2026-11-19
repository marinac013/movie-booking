#pragma once

#include "services/catalog_service.h"

namespace MovieBooking
{

/** @brief Represents the theater controller. */
class TheaterController
{
public:
    /** 
     * @brief Registers the theater routes. 
     * @param catalogService The catalog service.
     */
    static void RegisterRoutes(CatalogService& catalogService);
};

}