#include "api/movie_controller.h"
#include "api/api_response.h"

#include <drogon/drogon.h>

#include <iostream>

namespace MovieBooking
{

/** 
 *  @brief Registers the routes for the movie controller.
 *  @param catalogService The catalog service to use.
 */
void MovieController::RegisterRoutes(CatalogService& catalogService)
{
    /// GET /api/movies
    drogon::app().registerHandler(
        "/api/movies",
        [&catalogService](
            const drogon::HttpRequestPtr&,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback)
        {
            std::cout << "[ INFO ] Movie list requested." << std::endl;

            Json::Value response(Json::arrayValue);

            const auto movies = catalogService.GetMovies();

            for (const auto& movie : movies)
            {
                Json::Value item;
                item["id"] = movie.GetId();
                item["title"] = movie.GetTitle();

                response.append(item);
            }

            callback(ApiResponse::Json(response));
        },
        {drogon::Get});

    /// GET /api/movies/{id}
    drogon::app().registerHandler(
        "/api/movies/{1}",
        [&catalogService](
            const drogon::HttpRequestPtr&,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            int movieId)
        {
            std::cout << "[ INFO ] Movie details requested for movie "
                      << movieId << "." << std::endl;

            const auto movie = catalogService.GetMovieById(movieId);

            if (!movie.has_value())
            {
                callback(ApiResponse::Error(
                    "Movie not found.",
                    drogon::k404NotFound));
                return;
            }

            Json::Value response;
            response["id"] = movie->GetId();
            response["title"] = movie->GetTitle();

            callback(ApiResponse::Json(response));
        },
        {drogon::Get});

    /// GET /api/movies/{id}/theaters
    drogon::app().registerHandler(
        "/api/movies/{1}/theaters",
        [&catalogService](
            const drogon::HttpRequestPtr&,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            int movieId)
        {
            std::cout << "[ INFO ] Theaters requested for movie "
                      << movieId << "." << std::endl;

            const auto movie = catalogService.GetMovieById(movieId);

            if (!movie.has_value())
            {
                callback(ApiResponse::Error(
                    "Movie not found.",
                    drogon::k404NotFound));
                return;
            }

            Json::Value response(Json::arrayValue);

            const auto theaters =
                catalogService.GetTheatersShowingMovie(movieId);

            for (const auto& theater : theaters)
            {
                Json::Value item;
                item["id"] = theater.GetId();
                item["name"] = theater.GetName();

                response.append(item);
            }

            callback(ApiResponse::Json(response));
        },
        {drogon::Get});

    /// GET /api/movies/{id}/screenings
    drogon::app().registerHandler(
        "/api/movies/{1}/screenings",
        [&catalogService](
            const drogon::HttpRequestPtr&,
            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
            int movieId)
        {
            std::cout << "[ INFO ] Screenings requested for movie "
                      << movieId << "." << std::endl;

            const auto movie = catalogService.GetMovieById(movieId);

            if (!movie.has_value())
            {
                callback(ApiResponse::Error(
                    "Movie not found.",
                    drogon::k404NotFound));
                return;
            }

            Json::Value response(Json::arrayValue);

            const auto screenings =
                catalogService.GetScreeningsForMovie(movieId);

            for (const auto& screening : screenings)
            {
                Json::Value item;
                item["id"] = screening.GetId();
                item["movieId"] = screening.GetMovie().GetId();
                item["theaterId"] = screening.GetTheater().GetId();
                item["startTime"] = [&]() { 
                    auto t = std::chrono::system_clock::to_time_t(screening.GetStartTime()); 
                    if (auto* tm_ptr = std::localtime(&t)) {
                        std::ostringstream oss; 
                        oss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S"); 
                        return oss.str(); 
                    }
                    return std::string{}; 
                }();

                response.append(item);
            }

            callback(ApiResponse::Json(response));
        },
        {drogon::Get});
}

}