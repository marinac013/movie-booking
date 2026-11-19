#include "main.h"

int main()
{
    std::cout << "======================================" << std::endl;
    std::cout << MovieBooking::GetApplicationName() << std::endl;
    std::cout << "======================================" << std::endl;

    MovieBooking::Movie movie(1, "The Matrix");
    MovieBooking::Movie movie2(2, "Inception");
    MovieBooking::Movie movie3(3, "Interstellar");
    MovieBooking::Movie movie4(4, "The Dark Knight");
    MovieBooking::Movie movie5(5, "Pulp Fiction");
    MovieBooking::Movie movie6(6, "The Lord of the Rings: The Fellowship of the Ring");
    MovieBooking::Movie movie7(7, "The Lord of the Rings: The Two Towers");
    MovieBooking::Movie movie8(8, "The Lord of the Rings: The Return of the King");

    MovieBooking::Theater theater(1, "Cinestar");
    MovieBooking::Theater theater2(2, "Cineplexx");
    MovieBooking::Screening screening(1, movie, theater, std::chrono::system_clock::now());
    MovieBooking::Screening screening2(2, movie2, theater, std::chrono::system_clock::now()+std::chrono::hours(1));
    MovieBooking::Screening screening3(3, movie3, theater, std::chrono::system_clock::now()+ std::chrono::hours(2));
    MovieBooking::Screening screening4(4, movie4, theater, std::chrono::system_clock::now()+std::chrono::hours(3));
    MovieBooking::Screening screening5(5, movie5, theater, std::chrono::system_clock::now()+std::chrono::hours(4));
    MovieBooking::Screening screening6(6, movie6, theater, std::chrono::system_clock::now()+std::chrono::hours(5));
    MovieBooking::Screening screening7(7, movie7, theater, std::chrono::system_clock::now()+std::chrono::hours(6));
    MovieBooking::Screening screening8(8, movie8, theater, std::chrono::system_clock::now()+std::chrono::hours(7));

    MovieBooking::Screening screening9(9, movie, theater2, std::chrono::system_clock::now());
    MovieBooking::Screening screening10(10, movie2, theater2, std::chrono::system_clock::now()+std::chrono::hours(1));
    MovieBooking::Screening screening11(11, movie3, theater2, std::chrono::system_clock::now()+ std::chrono::hours(2));
    MovieBooking::Screening screening12(12, movie4, theater2, std::chrono::system_clock::now()+std::chrono::hours(3));
    MovieBooking::Screening screening13(13, movie5, theater2, std::chrono::system_clock::now()+std::chrono::hours(4));
    MovieBooking::Screening screening14(14, movie6, theater2, std::chrono::system_clock::now()+std::chrono::hours(5));
    MovieBooking::Screening screening15(15, movie7, theater2, std::chrono::system_clock::now()+std::chrono::hours(6));
    MovieBooking::Screening screening16(16, movie8, theater2, std::chrono::system_clock::now()+std::chrono::hours(7));

    /// Repositories
    MovieBooking::MovieRepository movieRepository;
    MovieBooking::TheaterRepository theaterRepository;
    MovieBooking::ScreeningRepository screeningRepository;
    MovieBooking::BookingRepository bookingRepository;

    screeningRepository.Add(screening);
    screeningRepository.Add(screening2);
    screeningRepository.Add(screening3);
    screeningRepository.Add(screening4);
    screeningRepository.Add(screening5);
    screeningRepository.Add(screening6);
    screeningRepository.Add(screening7);
    screeningRepository.Add(screening8);
    screeningRepository.Add(screening9);
    screeningRepository.Add(screening10);
    screeningRepository.Add(screening11);
    screeningRepository.Add(screening12);
    screeningRepository.Add(screening13);
    screeningRepository.Add(screening14);
    screeningRepository.Add(screening15);
    screeningRepository.Add(screening16);
    movieRepository.Add(movie);
    movieRepository.Add(movie2);
    movieRepository.Add(movie3);
    movieRepository.Add(movie4);
    movieRepository.Add(movie5);
    movieRepository.Add(movie6);
    movieRepository.Add(movie7);
    movieRepository.Add(movie8);
    theaterRepository.Add(theater);
    theaterRepository.Add(theater2);

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