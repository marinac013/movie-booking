#pragma once

#include <drogon/HttpResponse.h>
#include <json/json.h>

#include <string>

namespace MovieBooking
{

/** @brief Represents an API response. */
class ApiResponse
{
public:
    /** @brief Creates a JSON API response. */
    static drogon::HttpResponsePtr Json(
        const Json::Value& data,
        drogon::HttpStatusCode status = drogon::k200OK)
    {
        auto response =
            drogon::HttpResponse::newHttpJsonResponse(data);

        response->setStatusCode(status);
        return response;
    }

    /** @brief Creates an error API response. */
    static drogon::HttpResponsePtr Error(
        const std::string& message,
        drogon::HttpStatusCode status)
    {
        Json::Value response;
        response["error"] = message;

        return ApiResponse::Json(response, status);
    }
};

}