#include "api_client.h"

#include <sstream>

namespace MovieBooking
{

ApiClient::ApiClient(const std::string& baseUrl)
{
    this->httpClient = drogon::HttpClient::newHttpClient(baseUrl);
}

ApiResponse ApiClient::Get(const std::string& path)
{
    auto request = drogon::HttpRequest::newHttpRequest();

    request->setMethod(drogon::Get);
    request->setPath(path);

    return this->SendRequest(request);
}

ApiResponse ApiClient::Post(const std::string& path, const Json::Value& body)
{
    auto request = drogon::HttpRequest::newHttpJsonRequest(body);

    request->setPath(path);

    return this->SendRequest(request);
}

ApiResponse ApiClient::SendRequest(const drogon::HttpRequestPtr& request)
{
    ApiResponse result;

    if (!this->httpClient)
    {
        result.error = "HTTP client is not initialized.";
        return result;
    }

    const auto [requestResult, response] =
        this->httpClient->sendRequest(request, REQUEST_TIMEOUT_SECONDS);

    if (requestResult != drogon::ReqResult::Ok || !response)
    {
        result.error = "HTTP communication failed. Drogon result code: " +
                       std::to_string(static_cast<int>(requestResult));

        return result;
    }

    result.transportSuccess = true;
    result.statusCode = static_cast<int>(response->statusCode());
    result.rawBody = response->body();

    if (!result.rawBody.empty())
    {
        Json::CharReaderBuilder builder;
        std::string parseErrors;
        std::istringstream stream(result.rawBody);

        if (!Json::parseFromStream(builder, stream, &result.body, &parseErrors))
        {
            result.error = "Failed to parse JSON response: " + parseErrors;
        }
    }

    return result;
}

}