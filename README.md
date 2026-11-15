
# Movie Booking Backend

A cross-platform C++ backend service for online movie ticket booking.

## Overview

The application provides functionality for browsing movies, viewing theaters and screenings, checking seat availability and booking movie seats.

The backend is implemented in C++17 and uses CMake as its build system.

## Technology Stack

- C++17
- CMake 3.20+
- GoogleTest
- Drogon
- JsonCpp
- STL

## Prerequisites

- git
- C++17 compatible compiler (for example, g++)
- CMake 3.20 or newer
- Internet connection for initial GoogleTest download

```bash
sudo apt update
sudo apt install -y git gcc g++ cmake libjsoncpp-dev uuid-dev zlib1g-dev \
  libssl-dev libbrotli-dev libc-ares-dev libpq-dev libmariadb-dev \
  libsqlite3-dev libhiredis-dev

```

## Build Instructions

### Linux

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```

Run the application:

```bash
./build/movie_booking
```

### Windows

Using Visual Studio 2019 or newer:

```powershell
cmake -S . -B build

cmake --build build --config Debug
```

Run the application:

```powershell
.\build\Debug\movie_booking.exe
```

### macOS

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

cmake --build build --parallel
```

Run the application:

```bash
./build/movie_booking
```

## Running Tests

The test suite covers this application only; tests from fetched libraries are
disabled. Configure with `BUILD_TESTING=ON` to build and run the application tests:

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

On Windows with a multi-configuration generator:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

## Current Functionality

- Application initialization
- Cross-platform CMake configuration
- GoogleTest integration
- Basic application information module
- Movie and theater management
- Screening management
- Seat availability
- Ticket booking
- Concurrent booking protection
- HTTP Server (Drogon)
- REST API

## Future Development

- Doxygen Documentation
- Docker support
- Front-end Console Application
- clang-tidy

## REST API Interface for Backend Application
| Method | Endpoint | Purpose |
|---|---|---|
| GET | `/api/health` | Server health |
| GET | `/api/movies` | List movies |
| GET | `/api/movies/{id}` | Movie details |
| GET | `/api/movies/{id}/theaters` | Theaters showing a movie |
| GET | `/api/movies/{id}/screenings` | Screenings for a movie |
| GET | `/api/theaters/{id}/screenings` | Screenings at a theater |
| GET | `/api/screenings/{id}/seats` | Available seats |
| POST | `/api/screenings/{id}/bookings` | Book seats |
| GET | `/api/bookings/{id}` | Retrieve a booking |

## Limitations

The current version is an initial project setup. Booking functionality and persistent storage have not yet been implemented.