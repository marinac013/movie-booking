#pragma once

#include "services/catalog_service.h"

namespace MovieBooking
{

/** @brief Represents the screening controller. */
class ScreeningController
{
public:
    /** 
    * @brief Registers the screening routes.
    * @param catalogService The catalog service.
    */
    static void RegisterRoutes(CatalogService& catalogService);
};

}