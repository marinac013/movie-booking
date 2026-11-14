cmake_minimum_required(VERSION 3.20)

project(MovieBooking
    VERSION 1.0.0
    DESCRIPTION "Movie Ticket Booking Backend"
    LANGUAGES CXX
)

# --------------------------------------------------
# C++ Standard
# --------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# --------------------------------------------------
# Application Library
# --------------------------------------------------

add_library(movie_booking_core
    src/app_info.cpp
    src/domain/movie.cpp
    src/domain/theater.cpp
    src/domain/seat.cpp
    src/domain/screening.cpp
    src/domain/booking.cpp
    src/repos/movie_repo.cpp
    src/repos/theater_repo.cpp
    src/repos/screening_repo.cpp
    src/repos/booking_repo.cpp
    src/services/catalog_service.cpp
    src/services/booking_service.cpp
)

target_include_directories(movie_booking_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(movie_booking_core
    PUBLIC
        cxx_std_17
)


# --------------------------------------------------
# Application Executable
# --------------------------------------------------
find_package(Threads REQUIRED)

add_executable(movie_booking
    src/main.cpp
)

target_link_libraries(movie_booking
    PRIVATE
        movie_booking_core
    PUBLIC
        Threads::Threads
)

# --------------------------------------------------
# Compiler Warnings
# --------------------------------------------------

if(MSVC)

    target_compile_options(movie_booking_core PRIVATE /W4)
    target_compile_options(movie_booking PRIVATE /W4)

else()

    target_compile_options(movie_booking_core PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

    target_compile_options(movie_booking PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

endif()


# --------------------------------------------------
# Unit Testing
# --------------------------------------------------

include(CTest)

if(BUILD_TESTING)

    add_subdirectory(tests)

endif()