#include <drogon/drogon.h>

#include "domain/movie.h"
#include "domain/screening.h"
#include "domain/theater.h"
#include "repos/screening_repo.h"
#include "repos/booking_repo.h"
#include "services/booking_service.h"
#include "api/booking_controller.h"
#include "app_info.h"

#include <iostream>
#include <chrono>

int main()
{
    std::cout << "======================================" << std::endl;
    std::cout << MovieBooking::GetApplicationName() << std::endl;
    std::cout << "======================================" << std::endl;

    MovieBooking::Movie movie(1, "The Matrix");
    MovieBooking::Theater theater(1, "Cinestar");
    MovieBooking::Screening screening(1, movie, theater, std::chrono::system_clock::now());

    MovieBooking::ScreeningRepository screeningRepository;
    MovieBooking::BookingRepository bookingRepository;

    screeningRepository.Add(screening);

    MovieBooking::BookingService bookingService(
        screeningRepository,
        bookingRepository);

    MovieBooking::BookingController::RegisterRoutes(bookingService);

    std::cout << "[ INFO ] Application started successfully!" << std::endl;

    drogon::app()
        .addListener("0.0.0.0", 8080)
        .setThreadNum(4)
        .run();

    return 0;
}