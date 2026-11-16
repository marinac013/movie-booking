#pragma once

#include <drogon/HttpClient.h>
#include <json/json.h>

#include <string>

namespace MovieBooking
{

struct ApiResponse
{
    bool transportSuccess = false;
    int statusCode = 0;

    Json::Value body;
    std::string rawBody;
    std::string error;
};

class ApiClient
{
public:
    explicit ApiClient(const std::string& baseUrl);

    ApiResponse Get(const std::string& path);
    ApiResponse Post(const std::string& path, const Json::Value& body);
    bool IsHealthy();

private:
    ApiResponse SendRequest(const drogon::HttpRequestPtr& request);

    drogon::HttpClientPtr httpClient;
    static constexpr double REQUEST_TIMEOUT_SECONDS = 5.0;
};

}