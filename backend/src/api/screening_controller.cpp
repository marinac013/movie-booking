#include "api/screening_controller.h"
#include "api/api_response.h"

#include <drogon/drogon.h>

#include <iostream>

namespace MovieBooking
{

void ScreeningController::RegisterRoutes(CatalogService& catalogService)
{
    // GET /api/screenings/{id}/seats
    drogon::app().registerHandler(
        "/api/screenings/{1}/seats",
        [&catalogService](
            const drogon::HttpRequestPtr&,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            int screeningId)
        {
            std::cout << "[ INFO ] Available seats requested for screening "
                      << screeningId << "." << std::endl;

            const auto screening =
                catalogService.GetScreeningById(screeningId);

            if (!screening.has_value())
            {
                callback(ApiResponse::Error(
                    "Screening not found.",
                    drogon::k404NotFound));
                return;
            }

            Json::Value response(Json::arrayValue);

            const auto availableSeats =
                screening->GetAvailableSeats();

            for (const auto& seatId : availableSeats)
            {
                response.append(seatId);
            }

            callback(ApiResponse::Json(response));
        },
        {drogon::Get});
}

}