#include "api/booking_controller.h"
#include "api/api_response.h"

#include <drogon/drogon.h>

#include <iostream>
#include <string>
#include <vector>

namespace MovieBooking
{

void BookingController::RegisterRoutes(BookingService& bookingService)
{
    drogon::app().registerHandler(
    "/api/health",
    [](const drogon::HttpRequestPtr&,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback)
    {
        std::cout << "[ INFO ] Health check endpoint called." << std::endl;

        Json::Value response;
        response["status"] = "ok";
        response["service"] = "movie-booking";

        auto httpResponse =
            drogon::HttpResponse::newHttpJsonResponse(response);

        callback(httpResponse);
    },
    {drogon::Get});
    
    drogon::app().registerHandler(
        "/api/screenings/{1}/bookings",
        [&bookingService](
            const drogon::HttpRequestPtr& request,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            int screeningId)
        {
            std::cout << "[ INFO ] Booking request for screening "
                      << screeningId << "." << std::endl;

            const auto json = request->getJsonObject();

            if (!json ||
                !json->isMember("seats") ||
                !(*json)["seats"].isArray())
            {
                Json::Value error;
                error["error"] = "Request must contain a seats array.";

                auto response =
                    drogon::HttpResponse::newHttpJsonResponse(error);

                response->setStatusCode(
                    drogon::k400BadRequest);

                callback(response);
                return;
            }

            std::vector<std::string> seatIds;

            for (const auto& seat : (*json)["seats"])
            {
                if (!seat.isString())
                {
                    Json::Value error;
                    error["error"] = "Every seat ID must be a string.";

                    auto response =
                        drogon::HttpResponse::newHttpJsonResponse(error);

                    response->setStatusCode(
                        drogon::k400BadRequest);

                    callback(response);
                    return;
                }

                seatIds.push_back(seat.asString());
            }

            const BookingResult result =
                bookingService.BookSeats(screeningId, seatIds);

            Json::Value response;

            if (!result.IsSuccess())
            {
                response["error"] = "Booking failed.";

                // Map the application-level result to an HTTP status.
                drogon::HttpStatusCode statusCode =
                    drogon::k400BadRequest;

                switch (result.status)
                {
                    case BookingStatus::ScreeningNotFound:
                        statusCode = drogon::k404NotFound;
                        response["error"] = "Screening not found.";
                        break;

                    case BookingStatus::SeatUnavailable:
                        statusCode = drogon::k409Conflict;
                        response["error"] = "One or more seats are unavailable.";
                        break;

                    case BookingStatus::PersistenceError:
                        statusCode = drogon::k500InternalServerError;
                        response["error"] = "Could not save booking.";
                        break;

                    case BookingStatus::InvalidSeat:
                        response["error"] = "Invalid seat ID.";
                        break;

                    case BookingStatus::DuplicateSeat:
                        response["error"] = "Duplicate seat IDs.";
                        break;

                    case BookingStatus::EmptySeatSelection:
                        response["error"] = "No seats were selected.";
                        break;

                    case BookingStatus::Success:
                        break;
                }

                auto httpResponse =
                    drogon::HttpResponse::newHttpJsonResponse(response);

                httpResponse->setStatusCode(statusCode);
                callback(httpResponse);
                return;
            }

            const Booking& booking = *result.booking;

            response["bookingId"] = booking.GetId();
            response["screeningId"] = booking.GetScreeningId();
            response["seats"] = Json::Value(Json::arrayValue);

            for (const auto& seatId : booking.GetSeatIds())
            {
                response["seats"].append(seatId);
            }

            response["status"] = "success";

            auto httpResponse =
                drogon::HttpResponse::newHttpJsonResponse(response);

            httpResponse->setStatusCode(drogon::k201Created);

            callback(httpResponse);
        },
        {drogon::Post});
    
    // GET /api/bookings/{id}
    drogon::app().registerHandler(
        "/api/bookings/{1}",
        [&bookingService](
            const drogon::HttpRequestPtr&,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            int bookingId)
        {
            std::cout << "[ INFO ] Booking details requested for booking "
                      << bookingId << "." << std::endl;

            const auto booking =
                bookingService.GetBookingById(bookingId);

            if (!booking.has_value())
            {
                callback(ApiResponse::Error(
                    "Booking not found.",
                    drogon::k404NotFound));
                return;
            }

            Json::Value response;
            response["bookingId"] = booking->GetId();
            response["screeningId"] = booking->GetScreeningId();
            response["seats"] = Json::Value(Json::arrayValue);

            for (const auto& seatId : booking->GetSeatIds())
            {
                response["seats"].append(seatId);
            }

            response["status"] = "success";

            callback(ApiResponse::Json(response));
        },
        {drogon::Get});
}

}