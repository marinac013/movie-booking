#include "main.h"

int main()
{
    std::cout << "======================================" << std::endl;
    std::cout << MovieBooking::GetApplicationName() << std::endl;
    std::cout << "======================================" << std::endl;

    MovieBooking::Movie movie(1, "The Matrix");
    MovieBooking::Theater theater(1, "Cinestar");
    MovieBooking::Screening screening(1, movie, theater, std::chrono::system_clock::now());

    /// Repositories
    MovieBooking::MovieRepository movieRepository;
    MovieBooking::TheaterRepository theaterRepository;
    MovieBooking::ScreeningRepository screeningRepository;
    MovieBooking::BookingRepository bookingRepository;

    screeningRepository.Add(screening);
    movieRepository.Add(movie);

    /// Application services
    MovieBooking::BookingService bookingService(
        screeningRepository,
        bookingRepository);

    MovieBooking::CatalogService catalogService(
        movieRepository,
        theaterRepository,
        screeningRepository);

    /// Register API routes
    MovieBooking::MovieController::RegisterRoutes(catalogService);
    MovieBooking::TheaterController::RegisterRoutes(catalogService);
    MovieBooking::ScreeningController::RegisterRoutes(catalogService);
    MovieBooking::BookingController::RegisterRoutes(bookingService);

    MovieBooking::Config config = MovieBooking::Config::LoadConfig("config.toml");
    std::cout << "[ INFO ] Starting application on "
              << config.ip << ":" << config.port
              << " with " << config.threads << " threads." << std::endl
              << "[ INFO ] Application started successfully!" << std::endl;

    drogon::app()
        .addListener(config.ip, config.port)
        .setThreadNum(config.threads)
        .run();

    return 0;
}