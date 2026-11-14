
# Movie Booking Backend

A cross-platform C++ backend service for online movie ticket booking.

## Overview

The application provides functionality for browsing movies, viewing theaters and screenings, checking seat availability and booking movie seats.

The backend is implemented in C++17 and uses CMake as its build system.

## Technology Stack

- C++17
- CMake 3.20+
- GoogleTest
- STL

## Prerequisites

- git
- C++17 compatible compiler (for example, g++)
- CMake 3.20 or newer
- Internet connection for initial GoogleTest download

## Build Instructions

### Linux

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

cmake --build build -j$(nproc)
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

Execute all unit tests:

```bash
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

## Future Development

- Movie and theater management
- Screening management
- Seat availability
- Ticket booking
- Concurrent booking protection
- REST API
- Docker support

## Limitations

The current version is an initial project setup. Booking functionality and persistent storage have not yet been implemented.