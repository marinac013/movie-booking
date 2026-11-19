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

include(CTest)
set(_movie_booking_build_testing ${BUILD_TESTING})


# --------------------------------------------------
# Dependencies via FetchContent (JsonCpp & Drogon)
# --------------------------------------------------

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

FetchContent_GetProperties(
    jsoncpp
    SOURCE_DIR JSONCPP_SOURCE_DIR
)

# JsonCpp 1.9.5 adds a generated include directory that is not created by its
# FetchContent build. Its public headers are available directly from the source.
set_property(
    TARGET jsoncpp_lib
    PROPERTY INTERFACE_INCLUDE_DIRECTORIES
        "$<BUILD_INTERFACE:${JSONCPP_SOURCE_DIR}/include>"
)

# Tell Drogon to use the FetchContent version.
set(JSONCPP_INCLUDE_DIRS
    "${JSONCPP_SOURCE_DIR}/include"
    CACHE PATH "" FORCE
)

set(JSONCPP_LIBRARIES
    jsoncpp_lib
    CACHE STRING "" FORCE
)

FetchContent_Declare(
    drogon
    GIT_REPOSITORY https://github.com/drogonframework/drogon.git
    GIT_TAG        v1.9.8
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_CTL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(drogon)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        v3.4.0
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(tomlplusplus)

set(BUILD_TESTING ${_movie_booking_build_testing})

find_package(Threads REQUIRED)


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
    src/api/booking_controller.cpp
    src/api/movie_controller.cpp
    src/api/screening_controller.cpp
    src/api/theater_controller.cpp
    src/toml_wrapper.cpp
)

target_include_directories(movie_booking_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(movie_booking_core
    PUBLIC
        cxx_std_17
)

target_link_libraries(movie_booking_core
    PUBLIC
        jsoncpp_lib
        drogon
        Threads::Threads
        tomlplusplus::tomlplusplus
)


# --------------------------------------------------
# Application Executable
# --------------------------------------------------

add_executable(movie-booking-backend
    src/main.cpp
)

target_link_libraries(movie-booking-backend
    PRIVATE
        movie_booking_core
)

# Copy config.toml next to the compiled executable automatically on build
add_custom_command(TARGET movie-booking-backend POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/config.toml"
        "$<TARGET_FILE_DIR:movie-booking-backend>/config.toml"
)

# --------------------------------------------------
# Compiler Warnings
# --------------------------------------------------

if(MSVC)
    target_compile_options(movie_booking_core PRIVATE /W4)
    target_compile_options(movie-booking-backend PRIVATE /W4)
else()
    target_compile_options(movie_booking_core PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
    target_compile_options(movie-booking-backend PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()


# --------------------------------------------------
# Unit Testing
# --------------------------------------------------

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()