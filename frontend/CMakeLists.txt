cmake_minimum_required(VERSION 3.20)

project(MovieBookingFrontend
    VERSION 1.0.0
    DESCRIPTION "Movie Ticket Booking Frontend"
    LANGUAGES CXX
)


# --------------------------------------------------
# C++ Standard
# --------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
set(_movie_booking_frontend_build_testing ${BUILD_TESTING})


# --------------------------------------------------
# Dependencies via FetchContent (JsonCpp & Drogon)
# --------------------------------------------------

# Keep dependency test suites disabled while adding their targets.
set(BUILD_TESTING OFF)

include(FetchContent)

FetchContent_Declare(
    jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG        1.9.5
)

set(JSONCPP_WITH_TESTS OFF CACHE BOOL "" FORCE)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(jsoncpp)

FetchContent_Declare(
    drogon
    GIT_REPOSITORY https://github.com/drogonframework/drogon.git
    GIT_TAG        v1.9.8
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_CTL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(drogon)

set(BUILD_TESTING ${_movie_booking_frontend_build_testing})


# --------------------------------------------------
# Application Library
# --------------------------------------------------

add_library(movie_booking_frontend_core
    src/api_client.cpp
    src/menu.cpp
)

target_include_directories(movie_booking_frontend_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(movie_booking_frontend_core
    PUBLIC
        cxx_std_17
)

target_link_libraries(movie_booking_frontend_core
    PUBLIC
        drogon
        jsoncpp_lib
)


# --------------------------------------------------
# Application Executable
# --------------------------------------------------

add_executable(movie-booking-frontend
    src/main.cpp
)

target_link_libraries(movie-booking-frontend
    PRIVATE
        movie_booking_frontend_core
)


# --------------------------------------------------
# Compiler Warnings
# --------------------------------------------------

if(MSVC)
    target_compile_options(movie_booking_frontend_core PRIVATE /W4)
    target_compile_options(movie-booking-frontend PRIVATE /W4)
else()
    target_compile_options(movie_booking_frontend_core PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
    target_compile_options(movie-booking-frontend PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
