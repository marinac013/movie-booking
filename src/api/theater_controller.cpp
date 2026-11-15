#include "api/theater_controller.h"
#include "api/api_response.h"

#include <drogon/drogon.h>

namespace MovieBooking
{

void TheaterController::RegisterRoutes(CatalogService& catalogService)
{
    // GET /api/theaters/{id}/screenings
    drogon::app().registerHandler(
        "/api/theaters/{1}/screenings",
        [&catalogService](
            const drogon::HttpRequestPtr&,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            int theaterId)
        {
            Json::Value response(Json::arrayValue);

            const auto screenings =
                catalogService.GetScreeningsForTheater(theaterId);

            for (const auto& screening : screenings)
            {
                Json::Value item;
                item["id"] = screening.GetId();
                item["movieId"] = screening.GetMovie().GetId();
                item["theaterId"] = screening.GetTheater().GetId();

                response.append(item);
            }

            callback(ApiResponse::Json(response));
        },
        {drogon::Get});
}

}