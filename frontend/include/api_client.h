#pragma once

#include <drogon/HttpClient.h>
#include <json/json.h>

#include <string>

namespace MovieBooking
{

/** @brief A struct representing the response from the API. */
struct ApiResponse
{
    bool transportSuccess = false;
    int statusCode = 0;

    Json::Value body;
    std::string rawBody;
    std::string error;
};

/** @brief A class for interacting with the API. */
class ApiClient
{
public:
    /** 
     * @brief Constructs a new API client instance.
     * @param baseUrl The base URL of the API.
     */
    explicit ApiClient(const std::string& baseUrl);
    /** 
     * @brief Sends a GET request and returns the API response.
     * @param path The API endpoint path.
     * @return The API response.
     */
    ApiResponse Get(const std::string& path);
    /** 
     * @brief Sends a POST request and returns the API response.
     * @param path The API endpoint path.
     * @param body The request body.
     * @return The API response.
     */
    ApiResponse Post(const std::string& path, const Json::Value& body);
    /** 
     * @brief Checks if the API is healthy. 
     * @return True if the API is healthy, false otherwise.
     */
    bool IsHealthy();

private:
    /** 
     * @brief Sends a request and returns the API response. 
     * @param request The HTTP request to send.
     * @return The API response.
     */
    ApiResponse SendRequest(const drogon::HttpRequestPtr& request);
    /** @brief The HTTP client for making requests. */
    drogon::HttpClientPtr httpClient;
    /** @brief The timeout for API requests in seconds. */
    static constexpr double REQUEST_TIMEOUT_SECONDS = 5.0;
};

}